#include "ParticleEmitter.h"

#include <imgui.h>

ParticleEmitter::ParticleEmitter() :
    m_particles(nullptr), m_firstDead(0), m_maxParticles(0), m_vao(0),
    m_vbo(0), m_ibo(0), m_vertexData(nullptr), m_position(0, 0, 0)
{
    
}

ParticleEmitter::ParticleEmitter(unsigned int _maxParticles, unsigned int _emitRate,
    float _lifetimeMin, float _lifetimeMax, float _velocityMin, float _velocityMax,
    float _startSize, float _endSize, const glm::vec4& _startColor, const glm::vec4& _endColor) :
    m_maxParticles(_maxParticles), m_lifespanMin(_lifetimeMin), m_lifespanMax(_lifetimeMax),
    m_velocityMin(_velocityMin), m_velocityMax(_velocityMax), m_startSize(_startSize),
    m_endSize(_endSize), m_startColor(_startColor), m_endColor(_endColor)
{
    
}

ParticleEmitter::~ParticleEmitter()
{
    delete[] m_particles;
    delete[] m_vertexData;

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void ParticleEmitter::Initialise(unsigned int _maxParticles, unsigned int _emitRate,
    float _lifetimeMin, float _lifetimeMax, float _velocityMin, float _velocityMax,
    float _startSize, float _endSize, const glm::vec4& _startColor, const glm::vec4& _endColor)
{
    // Setup emit timers
    m_emitRate = 1.0f / _emitRate;
    m_emitTimer = 0;

    // Store the variables that we pass in
    m_lifespanMin = _lifetimeMin;
    m_lifespanMax = _lifetimeMax;
    
    m_velocityMin = _velocityMin;
    m_velocityMax = _velocityMax;
    
    m_startSize = _startSize;
    m_endSize = _endSize;
    
    m_startColor = _startColor;
    m_endColor = _endColor;

    m_maxParticles = _maxParticles;

    // Create a particle array
    m_particles = new Particle[m_maxParticles];
    m_firstDead = 0;

    // We need to create an array of vertices for the particles.
    // There needs to be four (4) vertices per particle to make a quad.
    // This will be generated as we update an emitter
    m_vertexData = new ParticleVertex[m_maxParticles * 4];

    // Indices that will be used for all required vertices
    unsigned int* indexData = new unsigned int[m_maxParticles * 6];

    for (unsigned int i = 0; i < m_maxParticles; i++)
    {
        indexData[i * 6 + 0] = i * 4 + 0;
        indexData[i * 6 + 1] = i * 4 + 1;
        indexData[i * 6 + 2] = i * 4 + 2;
        indexData[i * 6 + 3] = i * 4 + 2;
        indexData[i * 6 + 4] = i * 4 + 3;
        indexData[i * 6 + 5] = i * 4 + 0;
    }

    // Time to create the OpenGL buffers!
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 4 *
        sizeof(ParticleVertex), m_vertexData, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxParticles * 6 *
        sizeof(unsigned int), indexData, GL_STATIC_DRAW);

    // This is the position of the particle for their shader
    glEnableVertexAttribArray(0);

    // This is the color of the particle for their shader
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 16);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    delete[] indexData;
}

void ParticleEmitter::Emit()
{
    if (!isActive)
        return;
    
    // Check if there are any available particles for the system to emit
    if (m_firstDead >= m_maxParticles)
        return;

    // Return a dead particle to our available list
    Particle& particle = m_particles[m_firstDead++];

    // Reset the position of the returned particle
    particle.position = m_position;

    // Reset the lifespan of the returned particle
    particle.lifetime = 0;
    particle.lifespan = (rand() / (float)RAND_MAX) *
        (m_lifespanMax - m_lifespanMin) + m_lifespanMin;

    // Reset the velocity of the returned particle
    float velocity = (rand() / (float)RAND_MAX) *
        (m_velocityMax - m_velocityMin) + m_velocityMin;

    // Reset the color of the returned particle
    particle.color = m_startColor;

    // Reset the size of the returned particle
    particle.size = m_startSize;

    particle.velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
    particle.velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
    particle.velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;

    particle.velocity = normalize(particle.velocity) * velocity;
}

void ParticleEmitter::Update(float _dt, const glm::mat4& _cameraTransform)
{
    if (!isActive)
        return;
    
    // This will move and update all of the alive particles.
    // Then it will remove the dead particles.
    // It will then emit the particles based on the emitter's provided rate.
    // Finally we will then update the vertex array and setup our billboarding.

    m_emitTimer += _dt;

    // Spawn the particles
    while (m_emitTimer > m_emitRate)
    {
        Emit();
        m_emitTimer -= m_emitRate;
    }

    unsigned int quad = 0;

    // This will update all particles and make sure they work as billboarding quads
    for (unsigned int i = 0; i < m_firstDead; i++)
    {
        Particle* particle = &m_particles[i];

        particle->lifetime += _dt;

        if (particle->lifetime >= particle->lifespan)
        {
            *particle = m_particles[m_firstDead - 1];
            m_firstDead--;
        }
        else
        {
            // This will need to be changed when we use gravity
            if (m_hasGravity)
                particle->velocity += m_gravity;
            
            particle->position += particle->velocity * _dt;

            // Set the scale and color of the particle
            particle->size = glm::mix(m_startSize, m_endSize,
                particle->lifetime / particle->lifespan);

            particle->color = glm::mix(m_startColor, m_endColor,
                particle->lifetime / particle->lifespan);

            // Finally to set up the quad using the correct position, color and scale.
            float halfSize = particle->size * 0.5f;
            m_vertexData[quad * 4 + 0].position = glm::vec4( halfSize,  halfSize, 0, 1);
            m_vertexData[quad * 4 + 0].color = particle->color;

            m_vertexData[quad * 4 + 1].position = glm::vec4(-halfSize,  halfSize, 0, 1);
            m_vertexData[quad * 4 + 1].color = particle->color;

            m_vertexData[quad * 4 + 2].position = glm::vec4(-halfSize, -halfSize, 0, 1);
            m_vertexData[quad * 4 + 2].color = particle->color;

            m_vertexData[quad * 4 + 3].position = glm::vec4( halfSize, -halfSize, 0, 1);
            m_vertexData[quad * 4 + 3].color = particle->color;

            // Set up our billboard's transform
            glm::vec3 zAxis = normalize(glm::vec3(_cameraTransform[3]) - particle->position);
            glm::vec3 xAxis = cross(glm::vec3(_cameraTransform[1]), zAxis);
            glm::vec3 yAxis = cross(zAxis, xAxis);

            glm::mat4 billboard(glm::vec4(xAxis, 0),
                                glm::vec4(yAxis, 0),
                                glm::vec4(zAxis, 0),
                                glm::vec4(0, 0, 0, 1));

            m_vertexData[quad * 4 + 0].position = billboard *
            m_vertexData[quad * 4 + 0].position + glm::vec4(particle->position, 0);
            m_vertexData[quad * 4 + 1].position = billboard *
            m_vertexData[quad * 4 + 1].position + glm::vec4(particle->position, 0);
            m_vertexData[quad * 4 + 2].position = billboard *
            m_vertexData[quad * 4 + 2].position + glm::vec4(particle->position, 0);
            m_vertexData[quad * 4 + 3].position = billboard *
            m_vertexData[quad * 4 + 3].position + glm::vec4(particle->position, 0);

            ++quad;
        }
    }
}

void ParticleEmitter::Draw()
{
    // Draw imgui
    PSystemImGui();
    
    if (!isActive)
        return;
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_firstDead * 4 *
        sizeof(ParticleVertex), m_vertexData);
    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, m_firstDead * 6, GL_UNSIGNED_INT, 0);
}

void ParticleEmitter::PSystemImGui()
{
    ImGui::Begin("Particle System");

    ImGui::Checkbox("Emitter Enabled", &isActive);

    if (isActive)
    {
        ImGui::Indent();
        
        // Position
        ImGui::DragFloat3("Emitter Position", &m_position[0], 0.05f);

        // Emit rate - delay between particle emission
        ImGui::DragFloat("Emit Delay", &m_emitRate);
        
        // Lifespan - minimum / maximum lifespan of each particle
        ImGui::DragFloat("Lifespan Min", &m_lifespanMin);
        ImGui::DragFloat("Lifespan Max", &m_lifespanMax);

        // Velocity - minimum / maximum velocity of each particle
        ImGui::DragFloat("Velocity Min", &m_velocityMin);
        ImGui::DragFloat("Velocity Max", &m_velocityMax);

        // Size - start / end size of each particle over its lifetime
        ImGui::DragFloat("Start Size", &m_startSize);
        ImGui::DragFloat("End Size", &m_endSize);

        // Color - start / end color of each particle over its lifetime
        ImGui::ColorEdit4("Start Color", &m_startColor[0]);
        ImGui::ColorEdit4("End Color", &m_endColor[0]);

        // Gravity - is gravity enabled? What direction is the gravity?
        ImGui::Checkbox("Gravity Enabled", &m_hasGravity);

        if (m_hasGravity)
        {
            ImGui::Indent();
            ImGui::DragFloat3("Gravity Direction", &m_gravity[0], 0.01f);
            ImGui::Unindent();
        }

        ImGui::Unindent();
    }
    
    ImGui::End();
}

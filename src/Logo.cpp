#include"Logo.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(0, 359);

Logo::Logo() : width(2.0f), height(1.0f), vb("logoVertices"), ib("logoVertices"), texture("opengl.png", GL_CLAMP_TO_BORDER),  position(0.0f), model(1.0f), color(0.9f, 0.1f, 0.1f, 1.0f), hue(0), time(0.0f), oldTime(glfwGetTime()), changeColor(GL_FALSE) {
    VertexBufferLayout vl;
    for (auto& it : vb.getSectionSize()) {
        vl.push<GLfloat>(it);
    }
    va.addBufferAndLayout(vb, vl);
    vb.unbind();
    va.unbind();

    shader.push(GL_VERTEX_SHADER, "logo.vs");
    shader.push(GL_FRAGMENT_SHADER, "logo.fs");
    shader.buildShader();
    shader.use();

    va.bind();
    ib.bind();
    texture.bind(0);
    shader.setInt("outTexture1", 0);

    glm::vec2 direction = glm::vec2((rand() & 2) - 1, (rand() & 2) - 1);
    velocity = direction * glm::normalize(glm::vec2(glm::linearRand(glm::vec2(0.3f), glm::vec2(1.0f)))) * 3.0f;
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

    shader.setVec4(0, color);
    shader.setMat4("model", model);
}

Logo::~Logo() {}

void Logo::update(const glm::vec3& windowDims) {
    if (getCollisionX(windowDims.x)) {
        velocity.x *= -1;
        position.x = position.x >= 0.0f ? std::min(position.x, windowDims.x - (width / 2) - 0.001f) : std::max(position.x, -windowDims.x + (width / 2) - 0.001f);
        changeColor = GL_TRUE;
    }
    if (getCollisionY(windowDims.y)) {
        velocity.y *= -1;
        position.y = position.y >= 0.0f ? std::min(position.y, windowDims.y - (height / 2) - 0.001f) : std::max(position.y, -windowDims.y - (height / 2) + 0.001f);
        changeColor = GL_TRUE;
    }

    if (changeColor) {
        hue = (hue + 35) % 360;
        glm::vec3 rgbColor = glm::rgbColor(glm::vec3(hue, 0.8f, 1.0f));
        color = glm::vec4(rgbColor.x, rgbColor.y, rgbColor.z, 1.0f);
        shader.setVec4(0, color);
        changeColor = GL_FALSE;
    }

    GLfloat deltaTime = getDeltaTime();
    position += (velocity * deltaTime);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
    shader.setMat4("model", model);
}

GLboolean Logo::getCollisionX(const GLfloat& windowDim) {
    return glm::abs(position.x) >= windowDim - width / 2;
}

GLboolean Logo::getCollisionY(const GLfloat& windowDim) {
    return glm::abs(position.y) >= windowDim - height / 2;
}

const Shader& Logo::getShader() {
    return shader;
}

GLuint Logo::getIndicesCount() {
    return ib.getCount();
}

GLfloat Logo::getDeltaTime() {
    time = glfwGetTime();
    GLfloat deltaTime = time - oldTime;
    oldTime = time;

    return deltaTime;
}
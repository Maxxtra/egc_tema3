#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Lab9 : public gfxc::SimpleScene
    {
     public:
        Lab9();
        ~Lab9();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D *texture1 = NULL, Texture2D *texture2 = NULL);
        void RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
        Texture2D *CreateRandomTexture(unsigned int width, unsigned int height);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D *> mapTextures;
        GLuint randomTextureID;
        int morethanonetexture;

        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        // TODO(student): If you need any other class variables, define them here.
        int is_spot_light;
        float angle;
        glm::ivec2 resolution;
        float mouseAngle;
        bool rightmouse;
        float speed;
        bool coliz;
        bool cadou1;
        bool cadou2;
        bool cadou3;
        bool cadou4;
        bool cadou5;
        bool cadou6;
        bool cadou7;
        bool cadou8;
        bool cadou9;
        bool cadou10;
        bool cadou11;
    };
}   // namespace m1

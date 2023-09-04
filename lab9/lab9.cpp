#include "lab_m1/lab9/lab9.h"

#include <iostream>
#include <string>
#include <vector>

#include "lab_m1/lab9/transform3D.h"

using namespace std;
using namespace m1;

glm::vec3 point_light_pos[8];
glm::vec3 point_light_dir[8];
float tX = 0;
float tY = 13;
float tZ = -12.5;
float temporizator = 0;

// variabile pentru cadouri
int nr_cadouri1, nr_cadouri2, nr_cadouri3, nr_cadouri4, nr_cadouri5,
    nr_cadouri6, nr_cadouri7, nr_cadouri8, nr_cadouri9, nr_cadouri10,
    nr_cadouri11;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Lab9::Lab9() {}

Lab9::~Lab9() {}

void Lab9::Init() {
  resolution = window->GetResolution();
  mouseAngle = 0;
  rightmouse = false;
  coliz = true;
  cadou1 = true;
  cadou2 = true;
  cadou3 = true;
  cadou4 = true;
  cadou5 = true;
  cadou6 = true;
  cadou7 = true;
  cadou8 = true;
  cadou9 = true;
  cadou10 = true;
  cadou11 = true;
  nr_cadouri1 = 0;
  nr_cadouri2 = 0;
  nr_cadouri3 = 0;
  nr_cadouri4 = 0;
  nr_cadouri5 = 0;
  nr_cadouri6 = 0;
  nr_cadouri7 = 0;
  nr_cadouri8 = 0;
  nr_cadouri9 = 0;
  nr_cadouri10 = 0;
  nr_cadouri11 = 0;

  is_spot_light = 0;

  const string sourceTextureDir =
      PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "textures");

  // Load textures
  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "grass_bilboard.png").c_str(),
                    GL_REPEAT);
    mapTextures["grass"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["crate"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "earth.png").c_str(),
                    GL_REPEAT);
    mapTextures["earth"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "alb.jpg").c_str(), GL_REPEAT);
    mapTextures["alb"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "scoarta-de-copac.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["scoarta-de-copac"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "scoarta.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["scoarta"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "verde.png").c_str(),
                    GL_REPEAT);
    mapTextures["verde"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "luminite.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["luminite"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "piatra.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["piatra"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "pink.png").c_str(), GL_REPEAT);
    mapTextures["pink"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "cadou.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["cadou"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "zapada.jpg").c_str(),
                    GL_REPEAT);
    mapTextures["zapada"] = texture;
  }

  {
    Texture2D *texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS,
                              "vegetation", "bamboo", "bamboo.png")
                        .c_str(),
                    GL_REPEAT);
    mapTextures["bamboo"] = texture;
  }

  { mapTextures["random"] = CreateRandomTexture(25, 25); }

  // Load meshes
  {
    Mesh *mesh = new Mesh("cone");
    mesh->LoadMesh(
        PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"),
        "cone.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = new Mesh("box");
    mesh->LoadMesh(
        PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"),
        "box.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = new Mesh("sphere");
    mesh->LoadMesh(
        PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"),
        "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = new Mesh("bamboo");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS,
                             "vegetation", "bamboo"),
                   "bamboo.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  // Create a simple quad
  {
    vector<glm::vec3> vertices{
        glm::vec3(0.5f, 0.5f, 0.0f),    // top right
        glm::vec3(0.5f, -0.5f, 0.0f),   // bottom right
        glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
        glm::vec3(-0.5f, 0.5f, 0.0f),   // top left
    };

    vector<glm::vec3> normals{glm::vec3(0, 1, 1), glm::vec3(1, 0, 1),
                              glm::vec3(1, 0, 0), glm::vec3(0, 1, 0)};

    vector<glm::vec2> textureCoords{
        // TODO(student): Complete texture coordinates for the square
        // glm::vec2(0.0f, 0.0f)
        glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f)

    };

    vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};

    Mesh *mesh = new Mesh("square");
    mesh->InitFromData(vertices, normals, textureCoords, indices);
    meshes[mesh->GetMeshID()] = mesh;
  }

  // Create a shader program for drawing face polygon with the color of the
  // normal
  {
    Shader *shader = new Shader("LabShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9",
                                "shaders", "VertexShader.glsl"),
                      GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9",
                                "shaders", "FragmentShader.glsl"),
                      GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
  }

  {
    Shader *shader = new Shader("LabShader2");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9",
                                "shaders", "VertexLumini.glsl"),
                      GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9",
                                "shaders", "FragmentLumini.glsl"),
                      GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
  }

  // Light & material properties
  {
    lightPosition = glm::vec3(0, 1, 1);
    lightDirection = glm::vec3(0, -1, 0);

    point_light_pos[0] = glm::vec3(-2, 0.5, -2);
    point_light_dir[0] = glm::vec3(0, -1, 0);

    point_light_pos[1] = glm::vec3(1, 0, 1);
    point_light_dir[1] = glm::vec3(0, -1, 0);

    point_light_pos[2] = glm::vec3(-3, -0.3, 3);
    point_light_dir[2] = glm::vec3(0, -1, 0);

    point_light_pos[3] = glm::vec3(3, 0, 2);
    point_light_dir[3] = glm::vec3(0, -1, 0);

    point_light_pos[4] = glm::vec3(2.5, 1, -3);
    point_light_dir[4] = glm::vec3(0, -1, 0);

    point_light_pos[5] = glm::vec3(0, 0.4, 3);
    point_light_dir[5] = glm::vec3(0, -1, 0);

    point_light_pos[6] = glm::vec3(-4, 0.3, 0);
    point_light_dir[6] = glm::vec3(0, -1, 0);

    /*point_light_pos[13] = glm::vec3(0, 0.3, 1);
     point_light_dir[13] = glm::vec3(0, -1, 0);

     point_light_pos[8] = glm::vec3(-4, 0.3, 3);
     point_light_dir[8] = glm::vec3(0, -1, 0);

     point_light_pos[9] = glm::vec3(4, 0.3, 3);
     point_light_dir[9] = glm::vec3(0, -1, 0);

     point_light_pos[10] = glm::vec3(5, 0.3, -4.5);
     point_light_dir[10] = glm::vec3(0, -1, 0);

     point_light_pos[11] = glm::vec3(6.5, 0.3, 2);
     point_light_dir[11] = glm::vec3(0, -1, 0);

     point_light_pos[12] = glm::vec3(-6, 0.3, -5.5);
     point_light_dir[12] = glm::vec3(0, -1, 0);*/

    point_light_pos[7] = glm::vec3(-4, 0.3, 0);
    point_light_dir[7] = glm::vec3(0, -1, 0);

    materialShininess = 30;
    materialKd = 0.5;
    materialKs = 0.5;
  }
}

void Lab9::FrameStart() {
  // Clears the color buffer (using the previously set color) and depth buffer
  glClearColor(0, 0, 0.5, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::ivec2 resolution = window->GetResolution();
  // Sets the screen area where to draw
  glViewport(0, 0, resolution.x, resolution.y);
}

void Lab9::Update(float deltaTimeSeconds) {
  temporizator += deltaTimeSeconds;
  // piatra 1
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5, -4.6, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5, -4.7, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 2
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, -10.7, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, -10.8, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 3
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7, -10.6, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7, -10.7, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 4
  if (temporizator >= 23 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 5.3, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 23 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 5.2, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 4prim
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -26.9, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -27, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 5
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 10.2, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 10.1, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 5prim
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, -15.9, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, -16, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 6
  if (temporizator >= 65 && temporizator <= 100) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5, -5.6, 6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 65 && temporizator <= 100) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5, -5.7, 6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 7
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, -0.6, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, -0.7, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 8
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -0.6, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -0.7, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // piatra 9
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -11.7, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -11.8, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.1, 0.4));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix,
                     mapTextures["piatra"], mapTextures["crate"]);
  }

  // brad 1
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -0.3, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -0.7, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 2
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -4, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -4.3, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -4.7, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 3
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(12, -11, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(12, -11.3, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(12, -11.7, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 4
  if (temporizator >= 9 && temporizator <= 30) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 9, -8));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 9 && temporizator <= 30) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 8.7, -8));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 9 && temporizator <= 30) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 8.3, -8));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 4prim
  if (temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, -18.2, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, -18.6, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, -19, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 5
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, 6.9, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, 6.6, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, 6.2, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 5prim
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, -22, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, -22.3, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, -22.7, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 6
  if (temporizator >= 55 && temporizator <= 91) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -3, 4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 55 && temporizator <= 91) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -3.3, 4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 55 && temporizator <= 91) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -3.7, 4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 7
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, 6.9, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, 6.6, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 20 && temporizator <= 41) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, 6.2, -6));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 7prim
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, -22, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, -22.3, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 159 && temporizator <= 185) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(15, -22.7, 24));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 8
  if (temporizator >= 23 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 6, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 23 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 5.7, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 23 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 5.3, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 8prim
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -26.3, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -26.6, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -27, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 9
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 10.9, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 10.6, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 10.2, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 9prim
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -15.3, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -15.6, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, -16, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 10
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 10.9, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 10.6, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 10.2, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 10prim
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, -15.3, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, -15.6, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, -16, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 11
  if (temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -9, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -9.3, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -9.7, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // brad 12
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(4, -10, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["bamboo"], mapTextures["verde"]);
  }
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(4, -10.3, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix,
                     mapTextures["luminite"], mapTextures["alb"]);
  }
  if (temporizator >= 97 && temporizator <= 125) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(4, -10.7, 11));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["scoarta"], mapTextures["scoarta-de-copac"]);
  }

  // stalp 1
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, -0.4, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 49 && temporizator <= 75) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.4, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 2
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, -11.5, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 105 && temporizator <= 131) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, -10.7, 12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 3
  if (temporizator >= 15 && temporizator <= 35) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(13, 7.6, -7));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 15 && temporizator <= 35) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(13, 8.4, -7));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 3prim
  if (temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(13, -19, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(13, -18.2, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 4
  if (temporizator >= 24 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 5.5, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 24 && temporizator <= 45) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 6.3, -5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 4prim
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -27, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 168 && temporizator <= 200) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -26.2, 27));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 5
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 10.6, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 11.4, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 5prim
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -16, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -15.2, 16));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 6
  if (temporizator >= 2 && temporizator <= 11) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 12.7, -12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 2 && temporizator <= 11) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 13.5, -12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 6prim
  if (temporizator >= 120 && temporizator <= 138) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, -13, 14));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 120 && temporizator <= 138) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, -12.2, 14));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 7
  if (temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, -9.3, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, -8.5, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 8
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -4.3, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 60 && temporizator <= 95) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -3.5, 5));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 9
  if (temporizator >= 26 && temporizator <= 50) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 3.5, -3));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 26 && temporizator <= 50) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 4.3, -3));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 9prim
  if (temporizator >= 193 && temporizator <= 220) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -30.5, 31));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 193 && temporizator <= 220) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -29.7, 31));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // stalp 10
  if (temporizator >= 55 && temporizator <= 91) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, -3.3, 4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 1.5, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["pink"]);
  }
  if (temporizator >= 55 && temporizator <= 91) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, -2.5, 4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 0.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["crate"], mapTextures["random"]);
  }

  // cadou 1
  if (cadou1 == true && temporizator >= 53 && temporizator <= 83) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, -2.8, 3));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 2
  if (cadou2 == true && temporizator >= 53 && temporizator <= 80) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -1.8, 2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 3
  if (cadou3 == true && temporizator >= 53 && temporizator <= 83) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-12, -2.8, 3));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 4
  if (cadou4 == true && temporizator >= 15 && temporizator <= 35) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 7.2, -7));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }
  // cadou 4prim
  if (cadou4 == true && temporizator >= 146 && temporizator <= 165) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -18.7, 19));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 5
  if (cadou5 == true && temporizator >= 49 && temporizator <= 70) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 0.2, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 6
  if (cadou6 == true && temporizator >= 26 && temporizator <= 50) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 4.2, -4));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 6prim
  if (cadou6 == true && temporizator >= 193 && temporizator <= 220) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7, -30, 31));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 7
  if (cadou7 == true && temporizator >= 35 && temporizator <= 61) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 1.2, -1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 8
  if (cadou8 == true && temporizator >= 88 && temporizator <= 120) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-13, -9.8, 10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 9
  if (cadou9 == true && temporizator >= 80 && temporizator <= 110) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -7.8, 8));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 10
  if (cadou10 == true && temporizator >= 2 && temporizator <= 11) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(6, 12.2, -12));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 10prim
  if (cadou10 == true && temporizator >= 120 && temporizator <= 138) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(6, -13, 14));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 11
  if (cadou11 == true && temporizator >= 6 && temporizator <= 21) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 10.2, -10));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // cadou 11prim
  if (cadou11 == true && temporizator >= 130 && temporizator <= 150) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -15, 15));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["cadou"]);
  }

  // schior

  {
    speed = deltaTimeSeconds / 5;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(tX, tY, tZ));
    if (coliz == true) {
      tZ = tZ + speed;
      tY = tY - speed;
    }

    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    // modelMatrix = glm::rotate(modelMatrix, RADIANS(mouseAngle),
    // glm::vec3(1,0,0));

    if (rightmouse == true && coliz == true) {
      tX += speed;
    }
    if (rightmouse == false && coliz == true) {
      tX -= speed;
    }
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["alb"]);
  }

  // piatra 1
  if (sqrt((tX - 5) * (tX - 5) + (tZ - 5) * (tZ - 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 2
  if (sqrt((tX + 7) * (tX + 7) + (tZ - 11) * (tZ - 11)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 3
  if (sqrt((tX - 7) * (tX - 7) + (tZ - 11) * (tZ - 11)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 4
  if (sqrt((tX + 1) * (tX + 1) + (tZ + 5) * (tZ + 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 4prim
  if (sqrt((tX + 1) * (tX + 1) + (tZ - 27) * (tZ - 27)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 5
  if (sqrt((tX + 4) * (tX + 4) + (tZ + 10) * (tZ + 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 5prim
  if (sqrt((tX + 4) * (tX + 4) + (tZ - 16) * (tZ - 16)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 6
  if (sqrt((tX - 5) * (tX - 5) + (tZ - 6) * (tZ - 6)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 7
  if (sqrt((tX - 8) * (tX - 8) + (tZ - 1) * (tZ - 1)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 8
  if (sqrt((tX + 3) * (tX + 3) + (tZ - 1) * (tZ - 1)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // piatra 9
  if (sqrt((tX + 1) * (tX + 1) + (tZ - 9) * (tZ - 9)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 1
  if (sqrt((tX - 2) * (tX - 2) + (tZ - 1) * (tZ - 1)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 2
  if (sqrt((tX + 10) * (tX + 10) + (tZ - 5) * (tZ - 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 3
  if (sqrt((tX - 12) * (tX - 12) + (tZ - 12) * (tZ - 12)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 4
  if (sqrt((tX - 10) * (tX - 10) + (tZ + 8) * (tZ + 8)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 4prim
  if (sqrt((tX - 10) * (tX - 10) + (tZ - 19) * (tZ - 19)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 5
  if (sqrt((tX + 8) * (tX + 8) + (tZ + 6) * (tZ + 6)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 5prim
  if (sqrt((tX + 8) * (tX + 8) + (tZ - 24) * (tZ - 24)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 6
  if (sqrt((tX + 5) * (tX + 5) + (tZ - 4) * (tZ - 4)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 7
  if (sqrt((tX - 15) * (tX - 15) + (tZ + 6) * (tZ + 6)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 7prim
  if (sqrt((tX - 15) * (tX - 15) + (tZ - 24) * (tZ - 24)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 8
  if (sqrt((tX - 3) * (tX - 3) + (tZ + 5) * (tZ + 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 8prim
  if (sqrt((tX - 3) * (tX - 3) + (tZ - 27) * (tZ - 27)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 9
  if (sqrt((tX - 3) * (tX - 3) + (tZ + 10) * (tZ + 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 9prim
  if (sqrt((tX - 3) * (tX - 3) + (tZ - 16) * (tZ - 16)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 10
  if (sqrt((tX + 6) * (tX + 6) + (tZ + 10) * (tZ + 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 10prim
  if (sqrt((tX + 6) * (tX + 6) + (tZ - 16) * (tZ - 16)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 11
  if (sqrt((tX + 1) * (tX + 1) + (tZ - 10) * (tZ - 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // brad 12
  if (sqrt((tX - 4) * (tX - 4) + (tZ - 11) * (tZ - 11)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 1
  if (sqrt((tX - 1) * (tX - 1) + (tZ - 1) * (tZ - 1)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 2
  if (sqrt((tX + 11) * (tX + 11) + (tZ - 12) * (tZ - 12)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 3
  if (sqrt((tX - 13) * (tX - 13) + (tZ + 7) * (tZ + 7)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 3prim
  if (sqrt((tX - 13) * (tX - 13) + (tZ - 19) * (tZ - 19)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 4
  if (sqrt((tX + 5) * (tX + 5) + (tZ + 5) * (tZ + 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 4prim
  if (sqrt((tX + 5) * (tX + 5) + (tZ - 27) * (tZ - 27)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 5
  if (sqrt((tX + 5) * (tX + 5) + (tZ + 10) * (tZ + 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 5prim
  if (sqrt((tX + 5) * (tX + 5) + (tZ - 16) * (tZ - 16)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 6
  if (sqrt((tX + 11) * (tX + 11) + (tZ + 12) * (tZ + 12)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 6prim
  if (sqrt((tX + 11) * (tX + 11) + (tZ - 14) * (tZ - 14)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 7
  if (sqrt((tX - 8) * (tX - 8) + (tZ - 10) * (tZ - 10)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 8
  if (sqrt((tX + 3) * (tX + 3) + (tZ - 5) * (tZ - 5)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 9
  if (sqrt((tX + 10) * (tX + 10) + (tZ + 3) * (tZ + 3)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 9prim
  if (sqrt((tX + 10) * (tX + 10) + (tZ - 31) * (tZ - 31)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // stalp 10
  if (sqrt((tX - 10) * (tX - 10) + (tZ - 4) * (tZ - 4)) <= 0.1) {
    coliz = false;
    cout << "Scorul dumneavoastra este: "
         << nr_cadouri1 + nr_cadouri2 + nr_cadouri3 + nr_cadouri4 +
                nr_cadouri5 + nr_cadouri6 + nr_cadouri7 + nr_cadouri8 +
                nr_cadouri9 + nr_cadouri10 + nr_cadouri11
         << endl;
  }
  // cadou 1
  if (sqrt((tX - 1) * (tX - 1) + (tZ - 3) * (tZ - 3)) <= 0.1) {
    cadou1 = false;
    nr_cadouri1 += 1;
  }
  // cadou 2
  if (sqrt((tX + 5) * (tX + 5) + (tZ - 2) * (tZ - 2)) <= 0.1) {
    cadou2 = false;
    nr_cadouri2 += 1;
  }
  // cadou 3
  if (sqrt((tX + 12) * (tX + 12) + (tZ - 3) * (tZ - 3)) <= 0.1) {
    cadou3 = false;
    nr_cadouri3 += 1;
  }
  // cadou 4
  if (sqrt((tX + 10) * (tX + 10) + (tZ + 7) * (tZ + 7)) <= 0.1) {
    cadou4 = false;
    nr_cadouri4 += 1;
  }
  // cadou 4prim
  if (sqrt((tX + 10) * (tX + 10) + (tZ - 19) * (tZ - 19)) <= 0.1) {
    cadou4 = false;
    nr_cadouri4 += 1;
  }
  // cadou 5
  if (sqrt((tX - 10) * (tX - 10) + tZ * tZ) <= 0.1) {
    cadou5 = false;
    nr_cadouri5 += 1;
  }
  // cadou 6
  if (sqrt((tX - 8) * (tX - 8) + (tZ + 4) * (tZ + 4)) <= 0.1) {
    cadou6 = false;
    nr_cadouri6 += 1;
  }
  // cadou 6prim
  if (sqrt((tX - 7) * (tX - 7) + (tZ - 31) * (tZ - 31)) <= 0.1) {
    cadou6 = false;
    nr_cadouri6 += 1;
  }
  // cadou 7
  if (sqrt((tX - 3) * (tX - 3) + (tZ + 1) * (tZ + 1)) <= 0.1) {
    cadou7 = false;
    nr_cadouri7 += 1;
  }
  // cadou 8
  if (sqrt((tX + 13) * (tX + 13) + (tZ - 10) * (tZ - 10)) <= 0.1) {
    cadou8 = false;
    nr_cadouri8 += 1;
  }
  // cadou 9
  if (sqrt((tX + 1) * (tX + 1) + (tZ - 8) * (tZ - 8)) <= 0.1) {
    cadou9 = false;
    nr_cadouri9 += 1;
  }
  // cadou 10
  if (sqrt((tX - 6) * (tX - 6) + (tZ + 12) * (tZ + 12)) <= 0.1) {
    cadou10 = false;
    nr_cadouri10 += 1;
  }
  // cadou 10prim
  if (sqrt((tX - 6) * (tX - 6) + (tZ - 14) * (tZ - 14)) <= 0.1) {
    cadou10 = false;
    nr_cadouri10 += 1;
  }
  // cadou 11
  if (sqrt(tX * tX + (tZ + 10) * (tZ + 10)) <= 0.1) {
    cadou11 = false;
    nr_cadouri11 += 1;
  }
  // cadou 11prim
  if (sqrt(tX * tX + (tZ - 15) * (tZ - 15)) <= 0.1) {
    cadou11 = false;
    nr_cadouri11 += 1;
  }
  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix =
        glm::translate(modelMatrix, glm::vec3(tX - 0.1, tY - 0.3, tZ));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 1.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["pink"]);

    if (rightmouse == true) {
      modelMatrix *= transform3D::RotateOY(45);
    }
  }

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix =
        glm::translate(modelMatrix, glm::vec3(tX + 0.1, tY - 0.3, tZ));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 1.1));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix,
                     mapTextures["pink"]);

    if (rightmouse == true) {
      modelMatrix *= transform3D::RotateOY(45);
    }
  }

  // zapada

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix =
        glm::translate(modelMatrix, glm::vec3(tX, tY - 13, tZ + 12.5));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(40, 0, 40));
    RenderSimpleMesh2(meshes["box"], shaders["LabShader2"], modelMatrix,
                      glm::vec3(1, 1, 1));
  }
}

void Lab9::FrameEnd() {
  // DrawCoordinateSystem();
}

void Lab9::RenderSimpleMesh2(Mesh *mesh, Shader *shader,
                             const glm::mat4 &modelMatrix,
                             const glm::vec3 &color) {
  if (!mesh || !shader || !shader->GetProgramID()) return;

  // Render an object using the specified shader and the specified position
  glUseProgram(shader->program);

  // Set shader uniforms for light properties
  int light_position = glGetUniformLocation(shader->program, "light_position");
  glUniform3f(light_position, lightPosition.x, lightPosition.y,
              lightPosition.z);

  int light_direction =
      glGetUniformLocation(shader->program, "light_direction");
  glUniform3f(light_direction, lightDirection.x, lightDirection.y,
              lightDirection.z);

  // Set eye position (camera position) uniform
  glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
  int eye_position = glGetUniformLocation(shader->program, "eye_position");
  glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

  // Set material property uniforms (shininess, kd, ks, object color)
  int material_shininess =
      glGetUniformLocation(shader->program, "material_shininess");
  glUniform1i(material_shininess, materialShininess);

  int material_kd = glGetUniformLocation(shader->program, "material_kd");
  glUniform1f(material_kd, materialKd);

  int material_ks = glGetUniformLocation(shader->program, "material_ks");
  glUniform1f(material_ks, materialKs);

  int object_color = glGetUniformLocation(shader->program, "object_color");
  glUniform3f(object_color, color.r, color.g, color.b);

  // TODO(student): Set any other shader uniforms that you need
  int is_spot_light_location =
      glGetUniformLocation(shader->program, "is_spot_light");
  glUniform1i(is_spot_light_location, is_spot_light);

  GLuint location = glGetUniformLocation(shader->program, "point_light_pos");
  glUniform3fv(location, 3, glm::value_ptr(point_light_pos[0]));

  GLuint location1 = glGetUniformLocation(shader->program, "point_light_dir");
  glUniform3fv(location1, 3, glm::value_ptr(point_light_dir[0]));

  // Bind model matrix
  GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
  glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE,
                     glm::value_ptr(modelMatrix));

  // Bind view matrix
  glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
  int loc_view_matrix = glGetUniformLocation(shader->program, "View");
  glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

  // Bind projection matrix
  glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
  int loc_projection_matrix =
      glGetUniformLocation(shader->program, "Projection");
  glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE,
                     glm::value_ptr(projectionMatrix));

  // Draw the object
  glBindVertexArray(mesh->GetBuffers()->m_VAO);
  glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()),
                 GL_UNSIGNED_INT, 0);
}

void Lab9::RenderSimpleMesh(Mesh *mesh, Shader *shader,
                            const glm::mat4 &modelMatrix, Texture2D *texture1,
                            Texture2D *texture2) {
  if (!mesh || !shader || !shader->GetProgramID()) return;

  // Render an object using the specified shader and the specified position
  glUseProgram(shader->program);

  // Bind model matrix
  GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
  glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE,
                     glm::value_ptr(modelMatrix));

  // Bind view matrix
  glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
  int loc_view_matrix = glGetUniformLocation(shader->program, "View");
  glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

  // Bind projection matrix
  glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
  int loc_projection_matrix =
      glGetUniformLocation(shader->program, "Projection");
  glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE,
                     glm::value_ptr(projectionMatrix));

  // TODO(student): Set any other shader uniforms that you need
  if (texture2 == nullptr) {
    morethanonetexture = 0;
  } else {
    morethanonetexture = 1;
  }
  glUniform1i(glGetUniformLocation(shader->program, "tex2"),
              morethanonetexture);

  if (texture1) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
    glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
  }

  if (texture2) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
    glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
  }

  // Draw the object
  glBindVertexArray(mesh->GetBuffers()->m_VAO);
  glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()),
                 GL_UNSIGNED_INT, 0);
}

Texture2D *Lab9::CreateRandomTexture(unsigned int width, unsigned int height) {
  GLuint textureID = 0;
  unsigned int channels = 3;
  unsigned int size = width * height * channels;
  unsigned char *data = new unsigned char[size];

  // TODO(student): Generate random texture data
  for (int i = 0; i < size; i++) {
    data[i] = rand() % 9999999;
  }

  // TODO(student): Generate and bind the new texture ID
  glGenTextures(1, &randomTextureID);
  glBindTexture(GL_TEXTURE_2D, randomTextureID);

  if (GLEW_EXT_texture_filter_anisotropic) {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
  }
  // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and
  // WRAPPING MODE) using glTexParameteri
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  CheckOpenGLError();

  // Use glTexImage2D to set the texture data
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);

  // TODO(student): Generate texture mip-maps
  glGenerateMipmap(GL_TEXTURE_2D);
  CheckOpenGLError();

  // Save the texture into a wrapper Texture2D class for using easier later
  // during rendering phase
  Texture2D *texture = new Texture2D();
  texture->Init(randomTextureID, width, height, channels);

  SAFE_FREE_ARRAY(data);
  return texture;
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Lab9::OnInputUpdate(float deltaTime, int mods) {
  if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
    glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
    forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
  }
}

void Lab9::OnKeyPress(int key, int mods) {
  // Add key press event
  if (key == GLFW_KEY_R) {
    tX = 0;
    tY = 13;
    tZ = -12.5;
    coliz = true;
    cadou1 = true;
    cadou2 = true;
    cadou3 = true;
    cadou4 = true;
    cadou5 = true;
    cadou6 = true;
    cadou7 = true;
    cadou8 = true;
    cadou9 = true;
    cadou10 = true;
    cadou11 = true;
    temporizator = 0;
  }
}

void Lab9::OnKeyRelease(int key, int mods) {
  // Add key release event
}

void Lab9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
  // Add mouse move event
  resolution = window->GetResolution();
  mouseAngle = atan2(mouseX - 1280, mouseY - 720);
  if (mouseX > 1280 / 2) {
    rightmouse = true;
  } else {
    rightmouse = false;
  }
}

void Lab9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
  // Add mouse button press event
}

void Lab9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
  // Add mouse button release event
}

void Lab9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Lab9::OnWindowResize(int width, int height) {}

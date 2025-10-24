#include <glm/glm.hpp>
#include <vector>

struct Vertex {
  glm::vec3 pos;
  glm::vec3 normal;  
  glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    int type;
};

class Mesh{
    public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);

    private:
    //each Mesh object gets its own buffers (apparently)
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
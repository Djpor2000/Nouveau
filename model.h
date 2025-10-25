#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "shader.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;  
	glm::vec2 texCoords;
};

struct Texture {
		unsigned int id;
		std::string type;
};

class Mesh{
		public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			setupMesh();
		}
		void Draw(Shader &shader){
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for(unsigned int i = 0; i < textures.size(); i++)
			{
				 glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
				 // retrieve texture number (the N in diffuse_textureN)
					std::string number;
					std::string name = textures[i].type;
					if(name == "texture_diffuse")
						 number = std::to_string(diffuseNr++);
					else if(name == "texture_specular")
						 number = std::to_string(specularNr++);

					shader.setInt(("material." + name + number).c_str(), i);
					glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
			glActiveTexture(GL_TEXTURE0);

			// draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			}

		private:
		//each Mesh object gets its own buffers (apparently)
		unsigned int VAO, VBO, EBO;

		void setupMesh(){
			
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
								 &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glBindVertexArray(0);

		}
};

class Model{
	public:
	Model(char *path) {
		loadModel(path);
		}
	private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path){
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			
    	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        	std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        	return;
    	}
    	directory = path.substr(0, path.find_last_of('/'));

    	processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode *node, const aiScene *scene){
		
		for(unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        	meshes.push_back(processMesh(mesh, scene));	
		}

		for(unsigned int i = 0; i < node->mNumChildren; i++) {
        	processNode(node->mChildren[i], scene);
    	}
	}

	Mesh processMesh(aiMesh *mesh, const aiScene *scene){
		
	}
};
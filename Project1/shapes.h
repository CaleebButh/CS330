#pragma once
#pragma once
#include <types.h>
#include <numbers>
#include <tuple>
#include <vector>

struct Shapes {
    static inline void UpdateNormals(Vertex& p1, Vertex& p2, Vertex& p3) {
        glm::vec3 U = p2.Position - p1.Position;
        glm::vec3 V = p3.Position - p1.Position;

        auto normal = glm::cross(U, V);

        p1.Normal = normal;
        p2.Normal = normal;
        p3.Normal = normal;
    }

    
    static inline std::vector<Vertex> cubeVertices{
        // Front face
        {
                .Position = {-0.5f, 0.5f, 0.5f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {-0.5f, -0.5f, 0.5f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {0.5f, -0.5f, 0.5f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {0.5f, 0.5f, 0.5f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {1.f, 1.f}
        },
        // Right face
        {
                .Position = {0.5f, 0.5f, 0.5f},
                .Color = {0.5f, 0.5f, 0.5f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {0.5f, -0.5f, 0.5f},
                .Color = {0.5f, 0.5f, 0.5f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {0.5f, -0.5f, -0.5f},
                .Color = {0.5f, 0.5f, 0.5f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {0.5f, 0.5f, -0.5f},
                .Color = {0.5f, 0.5f, 0.5f},
                .Uv = {1.f, 1.f}
        },
        // Back face
        {
                .Position = {0.5f, 0.5f, -0.5f},
                .Color = {1.f, 1.f, 0.5f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {0.5f, -0.5f, -0.5f},
                .Color = {1.f, 1.f, 0.5f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {-0.5f, -0.5f, -0.5f},
                .Color = {1.f, 1.f, 0.5f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {-0.5f, 0.5f, -0.5f},
                .Color = {1.f, 1.f, 0.5f},
                .Uv = {1.f, 1.f}
        },
        // Left face
        {
                .Position = {-0.5f, 0.5f, -0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {-0.5f, -0.5f, -0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {-0.5f, -0.5f, 0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {-0.5f, 0.5f, 0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Uv = {1.f, 1.f}
        },
        // Top face
        {
                .Position = {-0.5f, 0.5f, -0.5f},
                .Color = {0.f, 1.f, 0.f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {-0.5f, 0.5f, 0.5f},
                .Color = {0.f, 1.f, 0.f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {0.5f, 0.5f, 0.5f},
                .Color = {0.f, 1.f, 0.f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {0.5f, 0.5f, -0.5f},
                .Color = {0.f, 1.f, 0.f},
                .Uv = {1.f, 1.f}
        },

        // bottom face
        {
                .Position = {0.5f, -0.5f, -0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Normal = {0, -1, 0},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {0.5f, -0.5f, 0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Normal = {0, -1, 0},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {-0.5f, -0.5f, 0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Normal = {0, -1, 0},
                .Uv = {1.f, 1.f}
        },
        {
                .Position = {-0.5f, -0.5f, -0.5f},
                .Color = {0.f, 0.5f, 0.f},
                .Normal = {0, -1, 0},
                .Uv = {1.f, 0.f}
        },
    };

    static inline std::vector<uint32_t> cubeElements{
            0, 1, 3, 1, 2, 3, // front face
            4, 5, 7, 5, 6, 7, // right face
            8, 9, 11, 9, 10, 11, // back face
            12, 13, 15, 13, 14, 15, // left face
            16, 17, 19, 17, 18, 19, // top face
            20, 21, 23, 21, 22, 23 // bottom face
    };

    static inline std::vector<uint32_t> pyramidIndices{
        // Front Tri
        2, 1, 0,
        // Right Tri
        5, 4, 3,
        // Back Tri
        8, 7, 6,
        // Left Tri
        11, 10, 9,
        // Bottom quad
        14, 13, 12,
        14, 15, 13,
    };

    static inline std::vector<Vertex> pyramidVertices{
        // front triangle
        {
                .Position = {-0.5f, 0.f, 0.5f},
                .Color = {1.f, 0.0f, 1.f},
                .Uv = {0.f, 0.f},
        },
        {
                .Position = {0.f, 1.f, 0.f},
                .Color = {1.f, 1.f, 1.f},
                .Uv = {0.5f, 1.f},
        },
        {
                .Position = {0.5f, 0.f, 0.5f},
                .Color = {1.0f, 1.f, 0.f},
                .Uv = {1.f, 0.f},
        },
        // right triangle
        {
                .Position = {0.5f, 0.f, 0.5f},
                .Color = {1.0f, 1.f, 0.f},
                .Uv = {0.f, 0.f},
        },
        {
                .Position = {0.f, 1.f, 0.f},
                .Color = {1.f, 1.f, 1.f},
                .Uv = {0.5f, 1.f},
        },
        {
                .Position = {0.5f, 0.f, -0.5f},
                .Color = {0.f, 0.f, 1.f},
                .Uv = {1.f, 0.f},
        },
        //back triangle
        {
                .Position = {0.5f, 0.f, -0.5f},
                .Color = {0.f, 0.f, 1.f},
                .Uv = {0.f, 0.f},
        },
        {
                .Position = {0.f, 1.f, 0.f},
                .Color = {1.f, 1.f, 1.f},
                .Uv = {0.5f, 1.f},
        },
        {
                .Position = {-0.5f, 0.f, -0.5f},
                .Color = {0.f, 1.f, 1.f},
                .Uv = {1.f, 0.f},
        },
        // left triangle
        {
                .Position = {-0.5f, 0.f, -0.5f},
                .Color = {0.f, 1.f, 1.f},
                .Uv = {0.f, 0.f},
        },
        {
                .Position = {0.f, 1.f, 0.f},
                .Color = {1.f, 1.f, 1.f},
                .Uv = {0.5f, 1.f},
        },
        {
                .Position = {-0.5f, 0.f, 0.5f},
                .Color = {1.f, 0.0f, 1.f},
                .Uv = {1.f, 0.f},
        },
        // bottom triangle
        {
                .Position = {-0.5f, 0.f, -0.5f},
                .Color = {0.f, 1.f, 1.f},
                .Uv = {0.f, 0.f},
        },
        {
                .Position = {-0.5f, 0.f, 0.5f},
                .Color = {1.f, 0.0f, 1.f},
                .Uv = {0.f, 1.f},
        },
        {
                .Position = {0.5f, 0.f, -0.5f},
                .Color = {0.f, 0.f, 1.f},
                .Uv = {1.f, 0.f},
        },
        {
                .Position = {0.5f, 0.f, 0.5f},
                .Color = {0.f, 0.f, 1.f},
                .Uv = {1.f, 1.f},
        }
    };

    static inline std::vector<Vertex> planeVertices{
        // Front face
        {
                .Position = {-0.5f, 0.5f, 0.0f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {0.f, 1.f}
        },
        {
                .Position = {-0.5f, -0.5f, 0.0f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {0.f, 0.f}
        },
        {
                .Position = {0.5f, -0.5f, 0.0f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {1.f, 0.f}
        },
        {
                .Position = {0.5f, 0.5f, 0.0f},
                .Color = {1.f, 0.5f, 0.5f},
                .Uv = {1.f, 1.f}
        }
    };

    static inline std::vector<uint32_t> planeElements{
        0, 1, 3, 1, 2, 3, // front face
    };


    static inline std::vector<Vertex> GetUnitCircleVertices(uint32_t sectorCount) {
        float sectorStep = 2.f * std::numbers::pi_v<float> / static_cast<float>(sectorCount);
        float sectorAngle; //radians

        std::vector<Vertex> vertices{};

        for (auto i = 0; i <= sectorCount; i++) {
            sectorAngle = static_cast<float>(i) * sectorStep;
            vertices.push_back({
                .Position = {
                       std::cos(sectorAngle),
                       std::sin(sectorAngle),
                       0
                }
                });
        }

        return vertices;
    };


    static inline std::tuple<std::vector<Vertex>, std::vector<uint32_t>> BuildCylinderSmooth(uint32_t sectorCount, float baseRadius, float height) {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        auto unitCircleVertices = GetUnitCircleVertices(sectorCount);

        /*
         *          BUILDING VERTEX ARRAY
         */

         // Build the sides
        for (auto i = 0; i < 2; i++) { // bottom half, top half
            float h = -height / 2.f + static_cast<float>(i) * height;
            float t = 1.f - i;      // texCoord

            // loop over all unit circle vertices
            uint32_t vertexIndex{ 0 };
            for (auto vertex : unitCircleVertices) {
                vertices.push_back({
                       .Position = {
                               vertex.Position.x * baseRadius,
                               vertex.Position.y * baseRadius,
                               h,
                       },
                       .Color = {
                               vertexIndex % 3 == 0 ? 1.f : 0.f,
                               vertexIndex % 3 == 1 ? 1.f : 0.f,
                               vertexIndex % 3 == 2 ? 1.f : 0.f,
                       },
                       .Normal = {
                               vertex.Position.x * baseRadius,
                               vertex.Position.y * baseRadius,
                               vertex.Position.z * baseRadius,
                       },
                       .Uv = {
                               static_cast<float>(vertexIndex) / static_cast<float>(sectorCount),
                               t
                       }
                    });

                vertexIndex++;
            }
        }
        auto baseCenterIndex = vertices.size();
        auto topCenterIndex = baseCenterIndex + sectorCount + 2;

        // Build the top and bottom
        for (auto i = 0; i < 2; i++) { // bottom half, top half
            float h = -height / 2.f + static_cast<float>(i) * height;
            float nz = -1.f + static_cast<float>(i) * 2;                 // z value of normal; -1 to 1

            // center point
            vertices.push_back({
                .Position = { 0, 0, h },
                .Color = {1.f, 1.f, 1.f},
                .Normal = { 0, 0, nz},
                .Uv = {0.5f, 0.5f}
                });

            // loop over all unit circle vertices
            uint32_t vertexIndex{ 0 };
            for (auto vertex : unitCircleVertices) {
                vertices.push_back({
                    .Position = {
                        vertex.Position.x * baseRadius,
                        vertex.Position.y * baseRadius,
                        h,
                    },
                    .Color = {
                        vertexIndex % 3 == 0 ? 1.f : 0.f,
                        vertexIndex % 3 == 1 ? 1.f : 0.f,
                        vertexIndex % 3 == 2 ? 1.f : 0.f,
                    },
                    .Normal = {
                        0,
                        0,
                        nz,
                    },
                    .Uv = {
                        -vertex.Position.x * 0.5f + 0.5f,
                        -vertex.Position.y * 0.5f + 0.5f
                    }
                    });

                vertexIndex++;
            }
        }

        /*
         *          BUILDING INDEX ARRAY
         */

         // indices for side surface

        uint32_t k1 = 0;
        uint32_t k2 = sectorCount + 1;
        for (auto i = 0; i < sectorCount; i++, k1++, k2++) {
            // 2 triangles per sector
            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }

        // bottom surface
        for (uint32_t i = 0, k = baseCenterIndex + 1; i < sectorCount; i++, k++) {
            if (i < sectorCount - 1) {
                indices.push_back(baseCenterIndex);
                indices.push_back(k + 1);
                indices.push_back(k);
            }
            else {
                indices.push_back(baseCenterIndex);
                indices.push_back(baseCenterIndex + 1);
                indices.push_back(k);
            }
        }

        for (uint32_t i = 0, k = topCenterIndex + 1; i < sectorCount; i++, k++) {
            if (i < sectorCount - 1) {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(k + 1);
            }
            else {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(topCenterIndex + 1);
            }
        }

        return { vertices, indices };
    }

    
};
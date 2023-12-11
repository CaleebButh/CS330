#include "desk.h"
#include<glm/gtc/matrix_transform.hpp>
#include "../shapes.h"

Desk::Desk(){
    createShaders();
    createMesh();
}

void Desk::Init(){

}

void Desk::Update(float deltaTime){

}

void Desk::createShaders(){
	_basicLitShader = std::make_shared<Shader>(Path("basic_lit.vert"), Path("basic_lit.frag"));
}

void Desk::createMesh(){
    auto deskTopTexture = std::make_shared<Texture>("desktop.jpg");
    auto deskTopMaterial = std::make_shared<Material>(_basicLitShader);
    deskTopMaterial->AddTexture(deskTopTexture);
    deskTopMaterial->Shininess = 1.f;
    deskTopMaterial->Roughness = 25.f;

    auto topMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    topMesh->Transform = glm::translate(topMesh->Transform, glm::vec3{ 3.0f, -4.0f, 3.0f });
    topMesh->Transform = glm::scale(topMesh->Transform, glm::vec3{ 2.5f, 0.25f, 5.f });
    
    _models.emplace_back(topMesh, deskTopMaterial);
    
    //create legs
    auto legTexture = std::make_shared<Texture>("leg.jpg");
    auto legMaterial = std::make_shared<Material>(_basicLitShader);
    legMaterial->AddTexture(legTexture);
    legMaterial->Shininess = 40.f;
    legMaterial->Roughness = 5.f;

    auto legMesh1 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    legMesh1->Transform = glm::translate(legMesh1->Transform, glm::vec3{ 2.f, -5.f, .65f });
    legMesh1->Transform = glm::scale(legMesh1->Transform, glm::vec3{ 0.25f,2.f,0.25f });

    auto legMesh2 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    legMesh2->Transform = glm::translate(legMesh2->Transform, glm::vec3{ 4.f, -5.f, .65f });
    legMesh2->Transform = glm::scale(legMesh2->Transform, glm::vec3{ 0.25f,2.f,0.25f });

    auto legMesh3 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    legMesh3->Transform = glm::translate(legMesh3->Transform, glm::vec3{ 2.f, -5.f, 5.33f });
    legMesh3->Transform = glm::scale(legMesh3->Transform, glm::vec3{ 0.25f,2.f,0.25f });

    auto legMesh4 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    legMesh4->Transform = glm::translate(legMesh4->Transform, glm::vec3{ 4.f, -5.f, 5.33f });
    legMesh4->Transform = glm::scale(legMesh4->Transform, glm::vec3{ 0.25f,2.f,0.25f });

    _models.emplace_back(legMesh1, legMaterial);
    _models.emplace_back(legMesh2, legMaterial);
    _models.emplace_back(legMesh3, legMaterial);
    _models.emplace_back(legMesh4, legMaterial);


    //create cup
    auto cupTexture = std::make_shared<Texture>("cup.jpg");
    auto cupMaterial = std::make_shared<Material>(_basicLitShader);
    cupMaterial->AddTexture(cupTexture);
    cupMaterial->Shininess = 1.f;
    cupMaterial->Roughness = 30.f;

    auto [cupVertices, cupIndices] = Shapes::BuildCylinderSmooth(15, 0.5f, 1.5f);

    auto cupMesh = std::make_shared<Mesh>(cupVertices, cupIndices, glm::vec3{ 1.f, 1.f, 1.f });
    cupMesh->Transform = glm::translate(cupMesh->Transform, glm::vec3{ 3.5f, -3.5f, 1.f });
    cupMesh->Transform = glm::rotate(cupMesh->Transform, glm::radians(90.f), glm::vec3{ 1.f, 0.f, 0.f });
    cupMesh->Transform = glm::rotate(cupMesh->Transform, glm::radians(-90.f), glm::vec3{ 0.f, 0.f, 1.f });

    cupMesh->Transform = glm::scale(cupMesh->Transform, glm::vec3{ 0.45f, 0.45f, 0.45f });

    _models.emplace_back(cupMesh, cupMaterial);
    

    //create lamp
    auto lampBase = std::make_shared<Texture>("leg.jpg");
    auto lampBaseMaterial = std::make_shared<Material>(_basicLitShader);
    lampBaseMaterial->AddTexture(lampBase);
    lampBaseMaterial->Shininess = 10.f;
    lampBaseMaterial->Roughness = 5.f;

    auto lampShaft = std::make_shared<Texture>("leg.jpg");
    auto lampShaftMaterial = std::make_shared<Material>(_basicLitShader);
    lampShaftMaterial->AddTexture(lampShaft);
    lampShaftMaterial->Shininess = 10.f;
    lampShaftMaterial->Roughness = 5.f;

    auto lampShade = std::make_shared<Texture>("cloth.jpg");
    auto lampShadeMaterial = std::make_shared<Material>(_basicLitShader);
    lampShadeMaterial->AddTexture(lampShade);
    lampShadeMaterial->Roughness = 10.f;

    auto lampBaseMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    lampBaseMesh->Transform = glm::translate(lampBaseMesh->Transform, glm::vec3{ 3.9f, -3.75f, 5.f });
    lampBaseMesh->Transform = glm::scale(lampBaseMesh->Transform, glm::vec3{ 0.5f,.25f,0.5f });

    _models.emplace_back(lampBaseMesh, lampBaseMaterial);

    auto [shaftVertices, shaftIndices] = Shapes::BuildCylinderSmooth(15, .05f, 1.5f);
    auto shaftMesh = std::make_shared<Mesh>(shaftVertices, shaftIndices, glm::vec3{ 1.f, 1.f, 1.f });
    shaftMesh->Transform = glm::translate(shaftMesh->Transform, glm::vec3{ 3.9f, -2.9f, 5.f });
    shaftMesh->Transform = glm::rotate(shaftMesh->Transform, glm::radians(90.f), glm::vec3{ 1.f, 0.f, 0.f });
    shaftMesh->Transform = glm::rotate(shaftMesh->Transform, glm::radians(-90.f), glm::vec3{ 0.f, 0.f, 1.f });

    _models.emplace_back(shaftMesh, lampShaftMaterial);

    auto lampShadeMesh = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidIndices, glm::vec3(1.f, 1.f, 1.f));
    lampShadeMesh->Transform = glm::translate(lampShadeMesh->Transform, glm::vec3{ 3.9f, -2.2f, 5.f });
    lampShadeMesh->Transform = glm::scale(lampShadeMesh->Transform, glm::vec3{ 1.5f,.5f,1.5f });

    _models.emplace_back(lampShadeMesh, lampShadeMaterial);

    //create computer
    auto computerArm = std::make_shared<Texture>("plastic.jpg");
    auto computerArmMaterial = std::make_shared<Material>(_basicLitShader);
    computerArmMaterial->AddTexture(computerArm);
    computerArmMaterial->Shininess = 2.5f;
    computerArmMaterial->Roughness = 2.f;

    auto computerArmMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    computerArmMesh->Transform = glm::translate(computerArmMesh->Transform, glm::vec3{ 2.9f, -3.75f, 3.f });
    computerArmMesh->Transform = glm::scale(computerArmMesh->Transform, glm::vec3{ 0.5f,.1f,0.8f });

    _models.emplace_back(computerArmMesh, computerArmMaterial);

    auto computerArmMesh2 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    computerArmMesh2->Transform = glm::translate(computerArmMesh2->Transform, glm::vec3{ 3.1f, -3.25f, 3.f });
    computerArmMesh2->Transform = glm::scale(computerArmMesh2->Transform, glm::vec3{ 0.1f,1.f,0.5f });

    _models.emplace_back(computerArmMesh2, computerArmMaterial);

    auto computerArmMesh3 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    computerArmMesh3->Transform = glm::translate(computerArmMesh3->Transform, glm::vec3{ 2.9f, -2.75f, 3.f });
    computerArmMesh3->Transform = glm::scale(computerArmMesh3->Transform, glm::vec3{ 0.5f,.1f,0.5f });

    _models.emplace_back(computerArmMesh3, computerArmMaterial);

    auto computerBody = std::make_shared<Texture>("alum.jpg");
    auto computerBodyMaterial = std::make_shared<Material>(_basicLitShader);
    computerBodyMaterial->AddTexture(computerBody);
    computerBodyMaterial->Shininess = 2.f;
    computerBodyMaterial->Roughness = 2.f;

    auto computerBodyMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    computerBodyMesh->Transform = glm::translate(computerBodyMesh->Transform, glm::vec3{ 2.6f, -2.75f, 3.f });
    computerBodyMesh->Transform = glm::rotate(computerBodyMesh->Transform, glm::radians(-90.f), glm::vec3{ 0.f, 1.f, 0.f });
    computerBodyMesh->Transform = glm::rotate(computerBodyMesh->Transform, glm::radians(90.f), glm::vec3{ 1.f, 0.f, 0.f });
    computerBodyMesh->Transform = glm::scale(computerBodyMesh->Transform, glm::vec3{ 2.5f,.1f,1.6f });

    _models.emplace_back(computerBodyMesh, computerBodyMaterial);

    auto computerScreen = std::make_shared<Texture>("doom.jpg");
    auto computerScreenMaterial = std::make_shared<Material>(_basicLitShader);
    computerScreenMaterial->AddTexture(computerScreen);
    computerScreenMaterial->Shininess = 3.f;
    

    auto computerScreenMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    computerScreenMesh->Transform = glm::translate(computerScreenMesh->Transform, glm::vec3{ 2.55f, -2.75f, 3.f });
    computerScreenMesh->Transform = glm::rotate(computerScreenMesh->Transform, glm::radians(-90.f), glm::vec3{ 0.f, 1.f, 0.f });
    computerScreenMesh->Transform = glm::rotate(computerScreenMesh->Transform, glm::radians(90.f), glm::vec3{ 1.f, 0.f, 0.f });
    computerScreenMesh->Transform = glm::scale(computerScreenMesh->Transform, glm::vec3{ 2.4f,.05f,1.5f });

    _models.emplace_back(computerScreenMesh, computerScreenMaterial);


    auto painting = std::make_shared<Texture>("bnb.jpg");
    auto paintingMaterial = std::make_shared<Material>(_basicLitShader);
    paintingMaterial->AddTexture(painting);
    paintingMaterial->Shininess = 0.f;
    paintingMaterial->Roughness = 1.f;

    auto paintingMesh = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));
    paintingMesh->Transform = glm::translate(paintingMesh->Transform, glm::vec3{ 8.7f, 0.f, 3.f });
    paintingMesh->Transform = glm::rotate(paintingMesh->Transform, glm::radians(-90.f), glm::vec3{ 0.f, 1.f, 0.f });
    paintingMesh->Transform = glm::rotate(paintingMesh->Transform, glm::radians(90.f), glm::vec3{ 1.f, 0.f, 0.f });
    paintingMesh->Transform = glm::scale(paintingMesh->Transform, glm::vec3{ 1.5f,.05f,2.4f });

    _models.emplace_back(paintingMesh, paintingMaterial);




 

}


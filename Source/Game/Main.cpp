#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Core/File.h"
#include "Engine.h"
#include "Texture.h"
#include "Game/Player.h"
#include "Game/SpaceGame.h"
#include "Resources/ResourceManager.h"
#include "Logger.h"
#include "EngineMinimal.h"
#include "Core/Factory.h"
#include <iostream>
#include <vector>
#include <memory>
//#include <Renderer/Texture.h>

class Animal {
public:
    virtual void Speak() = 0;

};

class Cat : public Animal {
public: 
    void Speak() override { std::cout << "meow\n"; }

};

class Dog : public Animal {
public: 
    void Speak() override { std::cout << "bark\n"; }
    void Fetch() { std::cout << "got the ball!\n"; }
};
class Bird : public Animal {
public: 
    void Speak() override { std::cout << "chirp\n"; }

};

enum class AnimalType {
    Cat,
    Dog,
    Bird
};





Animal* CreateAnimal(AnimalType id) {
    Animal* animal = nullptr;

    switch (id) {
    case AnimalType::Cat:
        animal = new Cat();
        break;
    case AnimalType::Dog:
        animal = new Dog();
        break;
    case AnimalType::Bird:
        animal = new Bird();

        break;
    default:
        break;

    }
    return animal;

}




int main(int argc, char* argv[]) {

    
    //viper::Logger::SetEnabledLevels(viper::LogLevel::Error);


    viper::file::SetCurrentDirectory("Assets");

    viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());


    auto animal = CreateAnimal(AnimalType::Cat);
    animal->Speak();
    auto dog = dynamic_cast<Dog*>(animal);
    if (dog) {
        dog->Fetch();

    }
    
    


    //std::cout << argc << std::endl;
    //for (int i = 0; i < argc; i++) {
    //    viper::Logger::Debug("arg {}: {}", i, argv[i]);
    //    //std::cout << argv[i] << std::endl;

    //}



    /*std::cout << "hello, world" << std::endl;
    int age{ 0 };
    std::cout << "enter age: ";
    if (!(std::cin >> age)) {
        std::cout << "invalid input\n";
    }
    else {
        std::cout << "you are " << (age * 365) << " days old.\n";

    }*/


    //std::fstream stream("test.txt");
    //if (!stream) {
    //    std::cout << "could not open file\n";

    //}
    ////std::cout << stream.rdbuf();
    //std::string line;
    //while (std::getline(stream, line)) {
    //    std::cout << line << std::endl;
    //}



    //viper::vec3 v{ 34.5f, 65.5f, 54.0f };
    //std::cout << v << std::endl;

    //std::string vstr("{ 23.4, 76.3 }");
    //std::stringstream sstream(vstr);

    //viper::vec2 v2;
    //sstream >> v2;

    //std::cout << v2 << std::endl;




    
    // initialize engine
    viper::Logger::Warning("initialize engine...");
    viper::GetEngine().Initialize();
    //viper::ResourceManager resourceManager;
    // initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");
    
    auto texture = viper::ResourceManager::Instance().Get<viper::Texture>("textures/blue_05.PNG", viper::GetEngine().GetRenderer());




    // create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280 , viper::random::getReal() * 1024 });
    }

    SDL_Event e;
    bool quit = false;
    float rotate = 0;

    // create texture, using shared_ptr so texture can be shared
    /*std::shared_ptr<viper::Texture> texture = std::make_shared<viper::Texture>();
    texture->Load("pixel-art-drawing-art-game-character-animation-png-favpng-4kk0ZkiGxyz1XXT8FpHiKJ4qy.JPG", viper::GetEngine().GetRenderer());*/





    // load the json data from a file
    std::string buffer;
    viper::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::Json::Load("json.txt", document);

    // read the age data from the json
    int age;
    viper::Json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;



    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }




        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());
       
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        viper::vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw(viper::GetEngine().GetRenderer());
        rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
        viper::GetEngine().GetRenderer().DrawTexture(*texture.get(), 30, 30, 45, 4);

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}

/*
    viper::vec2 speedz{ -140.0f, 0.0f };
    float length = speedz.Length();

    for (auto& star : stars) {
        star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

        if (star[0] > 1280) star[0] = 0;
        if (star[0] < 0) star[0] = 1280;

        viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
    }
*/
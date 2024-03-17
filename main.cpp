#include <iostream>
#include <string>
#include <Helper.h>


using namespace std;

class Menu{
private:
public:
    virtual void DisplayContent() const = 0;
    virtual Menu* TakeInput() = 0 ;
    Menu(){
        cout << "Constructed\n";
    };
    virtual ~Menu(){cout << "Deconstructed\n";}
};
class Main: public Menu{
public:
    void DisplayContent() const override{
        cout << "<--- Applications of Cellular Automata --->\n\n";
        cout << "1. Visualizations\n";
        cout << "2. Cryptography\n";
        cout << "3. Fractals\n";
        cout << "4. Exit\n";
    }
    Menu* TakeInput() override;

};
class Visualization: public Menu{
    void DisplayContent() const override{
        cout << "<--- Visualizations --->\n";
        cout << "1. Wolfram's Elementary rules\n";
        cout << "2. Conway's Game of Life\n";
        cout << "3. Belousov-Zhabotinsky\n";
        cout << "4. Custom 2D Cellular Automaton\n";
        cout << "5. Back\n";
    }
    Menu* TakeInput() override;
};
class Cryptography: public Menu{
    void DisplayContent() const override{
        cout << "<--- Cryptography --->\n";
        cout << "1. Image Encryption\n";
        cout << "2. Text Encryption\n";
        cout << "3. Back\n";
    }
    Menu* TakeInput() override;
};
class Fractal: public Menu{
    void DisplayContent() const override{
        cout << "<--- Fractals --->\n";
        cout << "1. Wolfram's Elementary Rules\n";
        cout << "2. More Fractals\n";
        cout << "3. Back\n";
    }
    Menu* TakeInput() override;
};

Menu* Main::TakeInput() {
    string input;
    cin >> input;
    if(input == "1"){
        return new Visualization();
    }
    if(input == "2"){
        return new Cryptography;
    }
    if(input == "3"){
        return new Fractal();
    }
    if(input == "4"){
        return nullptr;
    }
    return new Main();

}

Menu* Visualization::TakeInput() {
    string input;
    cin >> input;
    if(input == "1"){
        //Wolfram
        return new Visualization();
    }
    if(input == "2"){
        //Conways
        return new Visualization();
    }
    if(input == "3"){
        //Belousov
        return new Visualization();
    }
    if(input == "4"){
        //Custom
        return new Visualization();
    }
    if(input == "5"){
        //Back
        return new Main();
    }
    return new Visualization();


}

Menu* Fractal::TakeInput() {
    string input;
    cin >> input;
    if(input == "1"){
        //Wolfram
        return new Fractal();
    }
    if(input == "2"){
        //More
        return new Fractal();
    }
    if(input == "3"){
        //Back
        return new Main();
    }
    return new Fractal();

}

Menu* Cryptography::TakeInput() {
    string input;
    cin >> input;
    if(input == "1"){
        //Image
        return new Cryptography();
    }
    if(input == "2"){
        //Text
        return new Cryptography();
    }
    if(input == "3"){
        //Back
        return new Main();
    }
    return new Cryptography();

}

void runGame(Menu* current){
    if(current == nullptr)
        return;
    current->DisplayContent();
    Menu* next = current->TakeInput();
    delete current;
    runGame(next);
}


int main() {

    runGame(new Main());
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}

#include <iostream>
#include <string>
#include <Helper.h>
#include <vector>


using namespace std;


class ElementaryRule{
private:
    int ruleNumber;
    int maxLength;
    int maxDepth;
    int nrCurrGen;
    int maxGenerated;
    vector<int> ruleCod = vector<int>(8);
    vector<int> startGen;
    vector<int> currGen;
    vector<vector<int>> allGenerations;
public:
    explicit ElementaryRule(int ruleNumber = 90, int maxLength = 50, int maxDepth = 30, vector<int> startGen = {-1}){
        // Initialize integer variables
        this->ruleNumber = ruleNumber;
        this->maxLength = maxLength;
        this->maxDepth = maxDepth;
        this->nrCurrGen = 0;
        this->maxGenerated = 0;

        //Generate Rule Set
        int tempNumber = this->ruleNumber;
        for(int i = 0; i<8; i++)
        {
            ruleCod[i] = tempNumber & 1;
            tempNumber = tempNumber >> 1;

        }

        //Setting up vector lengths
        //Initialize initial generation
        this->currGen.resize(maxLength);

        this->startGen.resize(maxLength);
        for(int i = 0 ; i<maxLength; i++)
            this->startGen[i] = 0;
        if(startGen.size() == 1 && startGen[0] == -1)
            this->startGen[maxLength/2] = 1;
        else for(int i = 0 ; i<maxLength; i++)
                this->startGen[i] = startGen[i];

        allGenerations.resize(maxDepth);
        for(int i = 0 ; i<maxDepth;i++)
            allGenerations[i].resize(maxLength);
        for(int i = 0; i<maxLength;i++)
            allGenerations[0][i] = this->startGen[i], currGen[i] = this->startGen[i];
        cout << "Constructed Elementary Rule\n";
    }
    ElementaryRule(const ElementaryRule &other):ruleNumber(other.ruleNumber),maxLength(other.maxLength),maxDepth(other.maxDepth),nrCurrGen(other.nrCurrGen),maxGenerated(other.maxGenerated){
        cout << "I am starting from here\n";
        for(int i = 0 ; i < 8 ; i++)
            this->ruleCod[i] = other.ruleCod[i];
        this->startGen.resize(other.startGen.size());
        for(size_t i = 0 ; i<other.startGen.size(); i++)
            this->startGen[i] = other.startGen[i];
        this->allGenerations.resize(other.maxDepth);
        cout << "I am here 1\n";
        for(size_t i = 0 ; i<allGenerations.size(); i++)
            this->allGenerations[i].resize(maxLength);

        for(size_t i = 0 ; i<allGenerations.size(); i++)
            for(int j = 0 ; j<maxLength;j++)
                this->allGenerations[i][j] = other.allGenerations[i][j];
        this->currGen.resize(maxLength);
        for(int i = 0 ; i < maxLength; i++)
            this->currGen[i] = other.allGenerations[other.nrCurrGen][i];
        cout << "I am here 2\n";

    }



    ~ElementaryRule(){
        cout << "Deconstructed Elementary Rule\n";
    }
    friend ostream &operator<<(ostream &os, const ElementaryRule &rule) {
        os << "ruleNumber: " << rule.ruleNumber << " maxLength: " << rule.maxLength << " maxDepth: " << rule.maxDepth
           << " nrCurrGen: " << rule.nrCurrGen << " maxGenerated: " << rule.maxGenerated;
        return os;
    }
    ElementaryRule &operator=(const ElementaryRule &other){
        cout << "Stating\n";
        if(this == &other)
            return *this;
        cout << "I am here 1\n";
        this->ruleNumber = other.ruleNumber;
        this->maxLength = other.maxLength;
        this->maxDepth = other.maxDepth;
        this->nrCurrGen = other.nrCurrGen;
        this->maxGenerated = other.maxGenerated;
        cout << "I am here 2\n";
        for(int i = 0 ; i < 8 ; i++)
            this->ruleCod[i] = other.ruleCod[i];
        this->startGen.resize(other.startGen.size());
        for(size_t i = 0 ; i<other.startGen.size(); i++)
            this->startGen[i] = other.startGen[i];
        this->allGenerations.resize(other.maxDepth);
        cout << "I am here 3\n";
        for(size_t i = 0 ; i<allGenerations.size(); i++)
            this->allGenerations[i].resize(maxLength);
        for(size_t i = 0 ; i<allGenerations.size(); i++)
            for(int j = 0 ; j<maxLength;j++)
                this->allGenerations[i][j] = other.allGenerations[i][j];
        this->currGen.resize(maxLength);
        for(int i = 0 ; i < maxLength; i++)
            this->currGen[i] = other.allGenerations[other.nrCurrGen][i];

        return *this;
    }


    int getRuleNumber() const{
        return this->ruleNumber;
    }
    int getCurrGenNumber() const{
        return this->nrCurrGen;
    }
    vector<int> getCurrGeneration() const{
        return this->currGen;
    }
    vector<int> getStartGen() const{
        return this->startGen;
    }

    void setMaxDepth(int newMaxDepth){
        if(newMaxDepth < this->maxDepth)
        {
            //Throw Exception
            cout << "Can t decrease in depth\n";
            return;
        }
        this->maxDepth = newMaxDepth;
        this->allGenerations.resize(this->maxDepth);

    }
    void setMaxLength(int newMaxLength){
        if(newMaxLength < this->maxLength)
        {
            //Throw Exception
            cout << "Cant decrease in length\n";
            return;
        }
        this->maxLength = newMaxLength;
        this->currGen.resize(this->maxLength);
        for(int i = 0; i < maxDepth ; i++)
            allGenerations[i].resize(this->maxLength);

    }

     void CreateNextGen(){
        if(nrCurrGen < maxGenerated)
        {
            nrCurrGen++;
            for(int i = 0 ; i < maxLength; i++)
                currGen[i] = allGenerations[nrCurrGen][i];
            return;
        }
        if(nrCurrGen == maxDepth-1)
        {
            // Exception throw
            cout << "Max Size Reached";
            return;
        }
        nrCurrGen++;
        maxGenerated++;
        vector<int> temp(maxLength);
        for (int i = 0; i < maxLength; i++)
            temp[i] = currGen[(i - 1 + maxLength) % maxLength] * 4 + currGen[i] * 2 +
                      currGen[(i + maxLength + 1) % maxLength];
        for(int i = 0 ; i < maxLength; i++)
            currGen[i] = ruleCod[temp[i]], allGenerations[nrCurrGen][i] = currGen[i];

    }
    void MultipleGeneration(int depth){
        if(depth >= maxDepth)
        {
            //Throw Exception
            return;
        }
        if(depth < maxGenerated)
            return;
        for(int i = nrCurrGen; i < depth; i++)
            CreateNextGen();
    }
    void DisplayCurrentGeneration() const{
        cout << "Current generation "<<nrCurrGen<<"\n";
        for(int i = 0 ; i< maxLength; i++){
            cout << currGen[i];
        }
        cout << "\n";
    }
    void DisplayUpToCurrentGeneration() const {
        cout << "Generation from 0 to "<< nrCurrGen << ":\n";
        for(int i = 0;i<=nrCurrGen; i++)
        {
            for(int j = 0 ; j< maxLength;j++)
            {
                if(allGenerations[i][j])
                    cout << 0;
                else
                    cout << ' ';
            }
            cout << '\n';
        }
    }
    void UpdateCurrGeneration(int number){
        if(number < maxGenerated)
        {
            this->nrCurrGen = number;
            for(int i = 0 ; i< maxLength; i++)
            {
                currGen[i] = allGenerations[nrCurrGen][i];
            }
        }
        if(number > maxGenerated)
        {
            MultipleGeneration(number);
        }

    }
    void GenerateToMaxDepth(){
        MultipleGeneration(maxDepth-1);
    }
    void DisplayAll(){
        if(maxGenerated < maxDepth-1)
            GenerateToMaxDepth();
        UpdateCurrGeneration(maxDepth-1);
        DisplayUpToCurrentGeneration();

    }
};



class Menu{
private:
public:
    virtual void DisplayContent() const = 0;
    virtual Menu* TakeInput() = 0 ;
    Menu(){
        cout << "Constructed Menu\n";
    };
    virtual ~Menu(){cout << "Deconstructed Menu\n";}

    friend ostream &operator<<(ostream &os, const Menu &menu) {

        menu.DisplayContent();

        return os;
    }
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

class WolframVisualMenu: public Menu{
private:
    int state;
    int input;
    int ruleNumber;
    int maxDepth;
    int maxLength;
    ElementaryRule* ruleSet;
public:
    explicit WolframVisualMenu(int state = 0, int ruleNumber = 255, int maxDepth = 30, int maxLength = 50, ElementaryRule*ruleSet = new ElementaryRule(255,30,50)){
        this->state = state;
        this->ruleNumber = ruleNumber;
        this->maxDepth = maxDepth;
        this->maxLength = maxLength;
        this->input = 0;
        this->ruleSet = ruleSet;
    }
    void DisplayContent() const override{
        if(this->state == 0)
        {
            cout << "<--- Wolfram's Rules Visualization --->\n";
            cout << "Select (1, 2, 3) to change\nCurrent Settings:\n";
            cout << "1. Current Rule:"<<this->ruleNumber<<"\n";
            cout << "2. Maximum Length:"<<this->maxLength<<"\n";
            cout << "3. Maximum Depth:"<<this->maxDepth<<"\n";
            cout << "\n4. Generate!\n";
            cout << "5. Go Back\n";
        }
        if(this->state == 1)
        {
            cout << "<-- Wolfram's Rule " << this->ruleNumber << " -->\n";
            cout << "1. Next Generation\n";
            cout << "2. Previous Generation\n";
            cout << "3. Go to a generation by number\n";
            cout << "4. Complete all generation\n";
            cout << "5. Back\n";

            cout << this->ruleSet->getCurrGenNumber()<<'\n';
            ruleSet->DisplayCurrentGeneration();
            cout << '\n';
            ruleSet->DisplayUpToCurrentGeneration();
        }
    }
    Menu* TakeInput() override;
};


Menu* WolframVisualMenu::TakeInput(){
    cout << "\nCurrent Input: ";
    cin >> input;
    int rNum = this->ruleNumber;
    int mLen = this->maxLength;
    int mDep = this->maxDepth;
    int cState = this->state ;
    if(this->state == 0)
    {
        switch (input) {
            case 1:
                cout << "Insert new rule number: ";
                cin >> rNum;
                break;
            case 2:
                cout << "Insert new maximum length: ";
                cin >> mLen;
                break;
            case 3:
                cout << "Insert new maximum depth: ";
                cin >> mDep;
                break;
            case 4:
                cState = 1;
                //runWolframVisualization(rNum,mLen,mDep);
                break;
            case 5:
                delete this->ruleSet;
                return new Visualization();
        }
        delete this->ruleSet;
        return new WolframVisualMenu(cState,rNum,mDep,mLen, new ElementaryRule(rNum,mLen,mDep));
    }
    if(this->state == 1)
    {
        switch (input) {
            case 1:
                ruleSet->CreateNextGen();
                cout << ruleSet->getCurrGenNumber()<< '\n';
                cout << "Next Generation\n";
                break;
            case 2:
                if(ruleSet->getCurrGenNumber() > 0)
                ruleSet->UpdateCurrGeneration(ruleSet->getCurrGenNumber()-1);
                break;
            case 3:
                int tempInput;
                cout << "\nInput the generation number:";
                cin >> tempInput;
                ruleSet->UpdateCurrGeneration(tempInput);
                break;
            case 4:
                ruleSet->GenerateToMaxDepth();
                break;
            case 5:
                cState = 0;
                break;
            default:
                break;
        }

        return new WolframVisualMenu(cState,rNum,mDep,mLen, this->ruleSet);
    }
    delete this->ruleSet;
    return new WolframVisualMenu();
}

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
        return new WolframVisualMenu();
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
    else{
        cout << *current;
        //current->DisplayContent();
        Menu* next = current->TakeInput();
        delete current;
        runGame(next);
    }

}



int main() {
    // Functionalitati ale clasei Elementary rule
    ElementaryRule rule30(30);
    rule30.DisplayCurrentGeneration();
    rule30.CreateNextGen();
    rule30.DisplayCurrentGeneration();
    rule30.CreateNextGen();
    rule30.DisplayCurrentGeneration();
    rule30.MultipleGeneration(15);
    rule30.UpdateCurrGeneration(10);
    rule30.DisplayCurrentGeneration();
    rule30.DisplayUpToCurrentGeneration();
    rule30.MultipleGeneration(25);
    rule30.DisplayUpToCurrentGeneration();
    rule30.DisplayAll();
    cout << '\n' << rule30.getCurrGenNumber() << ' ' << rule30.getRuleNumber()<<'\n';
    for(int x : rule30.getCurrGeneration())
        cout << x << ' ';
    cout << '\n';
    for(int x : rule30.getStartGen())
        cout << x << ' ';
    cout << '\n';
    cout << rule30<<'\n';
    rule30.setMaxDepth(50);
    rule30.setMaxLength(100);
    cout << rule30<<'\n';
    ElementaryRule copyRule = rule30;
    cout << copyRule << '\n';

    // Functionalitate Aplicatie
    runGame(new Main());
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}

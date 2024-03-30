#include <iostream>
#include <string>
#include <Helper.h>
#include <vector>

/// @brief An elementary rule is an 1D automaton, that means a generation is represent by a vector(1D array). Every elementary rule has it's own rule set for creating the next generation. The number of every rule represent the rule set written in a shorter way by the binary representation of the number
/// @param ruleNumber The identifier for every rule
/// @param maxLength The maximum length of a generation
/// @param maxDepth The maximum number of generations which can be created
/// @param nrCurrGen The current generation number
/// @param maxGenerated In term of generation numbers, the biggest of them which was generated (<= maxDepth)
/// @param ruleCode It is a vector containing the rules of every generation
/// @param startGen The initial generation
/// @param currGen The current generation
/// @param allGenerations All generation which can be accessed by index of every generation
class ElementaryRule {
private:
    int ruleNumber;
    int maxLength;
    int maxDepth;
    int nrCurrGen;
    int maxGenerated;
    std::vector<int> ruleCod = std::vector<int>(8);
    std::vector<int> startGen;
    std::vector<int> currGen;
    std::vector<std::vector<int>> allGenerations;
public:
    /// @brief Constructor based on a specific rule identifier, length and depth
    explicit ElementaryRule(int ruleNumber = 90, int maxLength = 50, int maxDepth = 30,
                            std::vector<int> startGen = {-1}) {
        // Initialize integer variables
        this->ruleNumber = ruleNumber;
        this->maxLength = maxLength;
        this->maxDepth = maxDepth;
        this->nrCurrGen = 0;
        this->maxGenerated = 0;

        //Generate Rule Set
        int tempNumber = this->ruleNumber;
        for (int i = 0; i < 8; i++) {
            ruleCod[i] = tempNumber & 1;
            tempNumber = tempNumber >> 1;

        }

        //Setting up std::vector lengths
        //Initialize initial generation
        this->currGen.resize(maxLength);

        this->startGen.resize(maxLength);
        for (int i = 0; i < maxLength; i++)
            this->startGen[i] = 0;
        if (startGen.size() == 1 && startGen[0] == -1)
            this->startGen[maxLength / 2] = 1;
        else
            for (int i = 0; i < maxLength; i++)
                this->startGen[i] = startGen[i];

        allGenerations.resize(maxDepth);
        for (int i = 0; i < maxDepth; i++)
            allGenerations[i].resize(maxLength);
        for (int i = 0; i < maxLength; i++)
            allGenerations[0][i] = this->startGen[i], currGen[i] = this->startGen[i];
        std::cout << "Constructed Elementary Rule\n";
    }

    /// @brief Copy constructor
    ElementaryRule(const ElementaryRule &other) : ruleNumber(other.ruleNumber), maxLength(other.maxLength),
                                                  maxDepth(other.maxDepth), nrCurrGen(other.nrCurrGen),
                                                  maxGenerated(other.maxGenerated) {
        std::cout << "I am starting from here\n";
        for (int i = 0; i < 8; i++)
            this->ruleCod[i] = other.ruleCod[i];
        this->startGen.resize(other.startGen.size());
        for (size_t i = 0; i < other.startGen.size(); i++)
            this->startGen[i] = other.startGen[i];
        this->allGenerations.resize(other.maxDepth);
        std::cout << "I am here 1\n";
        for (size_t i = 0; i < allGenerations.size(); i++)
            this->allGenerations[i].resize(maxLength);

        for (size_t i = 0; i < allGenerations.size(); i++)
            for (int j = 0; j < maxLength; j++)
                this->allGenerations[i][j] = other.allGenerations[i][j];
        this->currGen.resize(maxLength);
        for (int i = 0; i < maxLength; i++)
            this->currGen[i] = other.allGenerations[other.nrCurrGen][i];
        std::cout << "I am here 2\n";

    }

    /// @brief Deconstruct
    ~ElementaryRule() {
        std::cout << "Deconstructed Elementary Rule\n";
    }

    /// @brief operator<<
    friend std::ostream &operator<<(std::ostream &os, const ElementaryRule &rule) {
        os << "ruleNumber: " << rule.ruleNumber << " maxLength: " << rule.maxLength << " maxDepth: " << rule.maxDepth
           << " nrCurrGen: " << rule.nrCurrGen << " maxGenerated: " << rule.maxGenerated;
        return os;
    }

    /// @brief operator=
    ElementaryRule &operator=(const ElementaryRule &other) {
        std::cout << "Stating\n";
        if (this == &other)
            return *this;
        std::cout << "I am here 1\n";
        this->ruleNumber = other.ruleNumber;
        this->maxLength = other.maxLength;
        this->maxDepth = other.maxDepth;
        this->nrCurrGen = other.nrCurrGen;
        this->maxGenerated = other.maxGenerated;
        std::cout << "I am here 2\n";
        for (int i = 0; i < 8; i++)
            this->ruleCod[i] = other.ruleCod[i];
        this->startGen.resize(other.startGen.size());
        for (size_t i = 0; i < other.startGen.size(); i++)
            this->startGen[i] = other.startGen[i];
        this->allGenerations.resize(other.maxDepth);
        std::cout << "I am here 3\n";
        for (size_t i = 0; i < allGenerations.size(); i++)
            this->allGenerations[i].resize(maxLength);
        for (size_t i = 0; i < allGenerations.size(); i++)
            for (int j = 0; j < maxLength; j++)
                this->allGenerations[i][j] = other.allGenerations[i][j];
        this->currGen.resize(maxLength);
        for (int i = 0; i < maxLength; i++)
            this->currGen[i] = other.allGenerations[other.nrCurrGen][i];

        return *this;
    }


    int getCurrGenNumber() const {
        return this->nrCurrGen;
    }

    void CreateNextGen() {
        if (nrCurrGen < maxGenerated) {
            nrCurrGen++;
            for (int i = 0; i < maxLength; i++)
                currGen[i] = allGenerations[nrCurrGen][i];
            return;
        }
        if (nrCurrGen == maxDepth - 1) {
            // Exception throw
            std::cout << "Max Size Reached";
            return;
        }
        nrCurrGen++;
        maxGenerated++;
        std::vector<int> temp(maxLength);
        for (int i = 0; i < maxLength; i++)
            temp[i] = currGen[(i - 1 + maxLength) % maxLength] * 4 + currGen[i] * 2 +
                      currGen[(i + maxLength + 1) % maxLength];
        for (int i = 0; i < maxLength; i++)
            currGen[i] = ruleCod[temp[i]], allGenerations[nrCurrGen][i] = currGen[i];

    }
    /// @brief Used to generate multiple generation, it is based on CreateNextGen()
    void MultipleGeneration(int depth) {
        if (depth >= maxDepth) {
            //Throw Exception
            return;
        }
        if (depth < maxGenerated)
            return;
        for (int i = nrCurrGen; i < depth; i++)
            CreateNextGen();
    }
    /// @brief Used for displaying the current generation
    void DisplayCurrentGeneration() const {
        std::cout << "Current generation " << nrCurrGen << "\n";
        for (int i = 0; i < maxLength; i++) {
            std::cout << currGen[i];
        }
        std::cout << "\n";
    }
    /// @brief Used to display all generation from 0 to nrCurrGen
    void DisplayUpToCurrentGeneration() const {
        std::cout << "Generation from 0 to " << nrCurrGen << ":\n";
        for (int i = 0; i <= nrCurrGen; i++) {
            for (int j = 0; j < maxLength; j++) {
                if (allGenerations[i][j])
                    std::cout << 0;
                else
                    std::cout << ' ';
            }
            std::cout << '\n';
        }
    }

    /// @brief It is used to go to a given generation by the parameter number
    void UpdateCurrGeneration(int number) {
        if (number < maxGenerated) {
            this->nrCurrGen = number;
            for (int i = 0; i < maxLength; i++) {
                currGen[i] = allGenerations[nrCurrGen][i];
            }
        }
        if (number > maxGenerated) {
            MultipleGeneration(number);
        }

    }

    /// @brief It is used to create all generations
    void GenerateToMaxDepth() {
        MultipleGeneration(maxDepth - 1);
    }

};

/// @brief Menu is a class which is used for the navigation menu of the program
class Menu {
private:
public:
    /// @brief DisplayContent - used for displaying the current menu
    virtual void DisplayContent() const = 0;

    /// @brief TakeInput - used for taking the user input and process it
    virtual Menu *TakeInput() = 0;

    Menu() {
        std::cout << "Constructed Menu\n";
    };

    /// @brief Deconstruct
    virtual ~Menu() { std::cout << "Deconstructed Menu\n"; }

    /// @brief operator<<
    friend std::ostream &operator<<(std::ostream &os, const Menu &menu) {

        menu.DisplayContent();

        return os;
    }
};


/// @brief Main - represent the main menu of the application
class Main : public Menu {
public:
    void DisplayContent() const override {
        std::cout << "<--- Applications of Cellular Automata --->\n\n";
        std::cout << "1. Visualizations\n";
        std::cout << "2. Cryptography\n";
        std::cout << "3. Fractals\n";
        std::cout << "4. Exit\n";
    }

    Menu *TakeInput() override;

};
/// @brief Visualization - represent a submenu in which are presented different ways to visualize automata
class Visualization : public Menu {
    void DisplayContent() const override {
        std::cout << "<--- Visualizations --->\n";
        std::cout << "1. Wolfram's Elementary rules\n";
        std::cout << "2. Conway's Game of Life\n";
        std::cout << "3. Belousov-Zhabotinsky\n";
        std::cout << "4. Custom 2D Cellular Automaton\n";
        std::cout << "5. Back\n";
    }

    Menu *TakeInput() override;
};

/// @brief Cryptography - represent a submenu, containing different ways to encrypt a photo or a text
class Cryptography : public Menu {
    void DisplayContent() const override {
        std::cout << "<--- Cryptography --->\n";
        std::cout << "1. Image Encryption\n";
        std::cout << "2. Text Encryption\n";
        std::cout << "3. Back\n";
    }

    Menu *TakeInput() override;
};

/// @brief Fractal - represent a submenu, containing different types of fractals
class Fractal : public Menu {
    void DisplayContent() const override {
        std::cout << "<--- Fractals --->\n";
        std::cout << "1. Wolfram's Elementary Rules\n";
        std::cout << "2. More Fractals\n";
        std::cout << "3. Back\n";
    }

    Menu *TakeInput() override;
};


/// @brief WolframVisualMenu - is a menu to preset the settings of a elementary rule which will be generated
class WolframVisualMenu : public Menu {
private:
    int state;
    int input;
    int ruleNumber;
    int maxDepth;
    int maxLength;
    ElementaryRule *ruleSet;
public:
    explicit WolframVisualMenu(int state = 0, int ruleNumber = 255, int maxDepth = 30, int maxLength = 50,
                               ElementaryRule *ruleSet = new ElementaryRule(255, 30, 50)) {
        this->state = state;
        this->ruleNumber = ruleNumber;
        this->maxDepth = maxDepth;
        this->maxLength = maxLength;
        this->input = 0;
        this->ruleSet = ruleSet;
    }

    void DisplayContent() const override {
        if (this->state == 0) {
            std::cout << "<--- Wolfram's Rules Visualization --->\n";
            std::cout << "Select (1, 2, 3) to change\nCurrent Settings:\n";
            std::cout << "1. Current Rule:" << this->ruleNumber << "\n";
            std::cout << "2. Maximum Length:" << this->maxLength << "\n";
            std::cout << "3. Maximum Depth:" << this->maxDepth << "\n";
            std::cout << "\n4. Generate!\n";
            std::cout << "5. Go Back\n";
        }
        if (this->state == 1) {
            std::cout << "<-- Wolfram's Rule " << this->ruleNumber << " -->\n";
            std::cout << "1. Next Generation\n";
            std::cout << "2. Previous Generation\n";
            std::cout << "3. Go to a generation by number\n";
            std::cout << "4. Complete all generation\n";
            std::cout << "5. Back\n";

            std::cout << this->ruleSet->getCurrGenNumber() << '\n';
            ruleSet->DisplayCurrentGeneration();
            std::cout << '\n';
            ruleSet->DisplayUpToCurrentGeneration();
        }
    }

    Menu *TakeInput() override;
};


Menu *WolframVisualMenu::TakeInput() {
    std::cout << "\nCurrent Input: ";
    std::cin >> input;
    int rNum = this->ruleNumber;
    int mLen = this->maxLength;
    int mDep = this->maxDepth;
    int cState = this->state;
    if (this->state == 0) {
        switch (input) {
            case 1:
                std::cout << "Insert new rule number: ";
                std::cin >> rNum;
                break;
            case 2:
                std::cout << "Insert new maximum length: ";
                std::cin >> mLen;
                break;
            case 3:
                std::cout << "Insert new maximum depth: ";
                std::cin >> mDep;
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
        return new WolframVisualMenu(cState, rNum, mDep, mLen, new ElementaryRule(rNum, mLen, mDep));
    }
    if (this->state == 1) {
        switch (input) {
            case 1:
                ruleSet->CreateNextGen();
                std::cout << ruleSet->getCurrGenNumber() << '\n';
                std::cout << "Next Generation\n";
                break;
            case 2:
                if (ruleSet->getCurrGenNumber() > 0)
                    ruleSet->UpdateCurrGeneration(ruleSet->getCurrGenNumber() - 1);
                break;
            case 3:
                int tempInput;
                std::cout << "\nInput the generation number:";
                std::cin >> tempInput;
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

        return new WolframVisualMenu(cState, rNum, mDep, mLen, this->ruleSet);
    }
    delete this->ruleSet;
    return new WolframVisualMenu();
}

Menu *Main::TakeInput() {
    std::string input;
    std::cin >> input;
    if (input == "1") {
        return new Visualization();
    }
    if (input == "2") {
        return new Cryptography;
    }
    if (input == "3") {
        return new Fractal();
    }
    if (input == "4") {
        return nullptr;
    }
    return new Main();

}

Menu *Visualization::TakeInput() {
    std::string input;
    std::cin >> input;
    if (input == "1") {
        //Wolfram
        return new WolframVisualMenu();
    }
    if (input == "2") {
        //Conways
        return new Visualization();
    }
    if (input == "3") {
        //Belousov
        return new Visualization();
    }
    if (input == "4") {
        //Custom
        return new Visualization();
    }
    if (input == "5") {
        //Back
        return new Main();
    }
    return new Visualization();


}

Menu *Fractal::TakeInput() {
    std::string input;
    std::cin >> input;
    if (input == "1") {
        //Wolfram
        return new Fractal();
    }
    if (input == "2") {
        //More
        return new Fractal();
    }
    if (input == "3") {
        //Back
        return new Main();
    }
    return new Fractal();

}

Menu *Cryptography::TakeInput() {
    std::string input;
    std::cin >> input;
    if (input == "1") {
        //Image
        return new Cryptography();
    }
    if (input == "2") {
        //Text
        return new Cryptography();
    }
    if (input == "3") {
        //Back
        return new Main();
    }
    return new Cryptography();

}

/// @brief runGame - The mechanism of the menu, it is used to to travers through the application
void runGame(Menu *current) {
    if (current == nullptr)
        return;
    else {
        std::cout << *current;
        //current->DisplayContent();
        Menu *next = current->TakeInput();
        delete current;
        runGame(next);
    }

}


int main() {
    // Functionalitate Aplicatie
    runGame(new Main());
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}

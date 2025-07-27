/*
=========================================
COMPUTE CC (CYCLOMATIC COMPLEXITY) QUESTION
=========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Cyclomatic Complexity (CC) Analysis System with the following requirements:

1. Base Class: CodeElement (elementId, name, type, complexity)
2. Derived Classes:
   - Function (parameters, statements, controlStructures)
   - Class (methods, attributes, inheritanceDepth)
   - Module (functions, classes, dependencies)
   - Project (modules, totalComplexity)
3. ComplexityCalculator Class: (analysis rules, thresholds)
4. Features:
   - Calculate cyclomatic complexity for different code elements
   - Analyze control flow structures
   - Generate complexity reports
   - Identify high complexity areas
   - Suggest refactoring recommendations

IMPLEMENTATION REQUIREMENTS:
- Use inheritance hierarchy with virtual functions
- Implement encapsulation with proper access modifiers
- Use constructors and destructors
- Implement static members for tracking
- Use friend functions for cross-class operations
- Implement operator overloading for comparisons
- Use templates for generic operations
- Handle exceptions for invalid operations
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class ComplexityException : public exception {
private:
    string message;
public:
    ComplexityException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class AnalysisException : public exception {
private:
    string message;
public:
    AnalysisException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// CONTROL STRUCTURE CLASS
// ==========================================

class ControlStructure {
private:
    string type; // "if", "while", "for", "switch", "case", "catch"
    int complexity;
    string condition;

public:
    ControlStructure(string t, string cond = "") : type(t), condition(cond) {
        if (type == "if" || type == "while" || type == "for") {
            complexity = 1;
        } else if (type == "switch") {
            complexity = 1;
        } else if (type == "case") {
            complexity = 1;
        } else if (type == "catch") {
            complexity = 1;
        } else {
            complexity = 0;
        }
    }

    // Getters
    string getType() const { return type; }
    int getComplexity() const { return complexity; }
    string getCondition() const { return condition; }

    // Display control structure
    void display() const {
        cout << "Type: " << type << ", Complexity: " << complexity;
        if (!condition.empty()) {
            cout << ", Condition: " << condition;
        }
        cout << endl;
    }

    // Operator overloading
    bool operator==(const ControlStructure& other) const {
        return type == other.type && condition == other.condition;
    }

    bool operator<(const ControlStructure& other) const {
        return complexity < other.complexity;
    }

    friend ostream& operator<<(ostream& os, const ControlStructure& cs);
};

ostream& operator<<(ostream& os, const ControlStructure& cs) {
    os << cs.type << "(" << cs.complexity << ")";
    return os;
}

// ==========================================
// BASE CLASS: CODE ELEMENT
// ==========================================

class CodeElement {
protected:
    int elementId;
    string name;
    string type;
    int complexity;
    static int elementCounter;

public:
    CodeElement(string n, string t) : name(n), type(t), complexity(1) {
        elementCounter++;
        elementId = elementCounter;
    }

    virtual ~CodeElement() {
        elementCounter--;
    }

    // Virtual functions for polymorphism
    virtual void calculateComplexity() {
        complexity = 1; // Base complexity
    }

    virtual void display() const {
        cout << "Element ID: " << elementId << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Complexity: " << complexity << endl;
    }

    virtual string getComplexityLevel() const {
        if (complexity <= 5) return "Low";
        else if (complexity <= 10) return "Medium";
        else if (complexity <= 15) return "High";
        else return "Very High";
    }

    // Getters
    int getElementId() const { return elementId; }
    string getName() const { return name; }
    string getType() const { return type; }
    int getComplexity() const { return complexity; }

    // Setters
    void setName(string n) { name = n; }
    void setType(string t) { type = t; }
    void setComplexity(int c) { 
        if (c < 1) {
            throw ComplexityException("Complexity must be at least 1");
        }
        complexity = c; 
    }

    // Static function
    static int getElementCounter() { return elementCounter; }

    // Operator overloading
    bool operator==(const CodeElement& other) const {
        return elementId == other.elementId;
    }

    bool operator<(const CodeElement& other) const {
        return complexity < other.complexity;
    }

    bool operator>(const CodeElement& other) const {
        return complexity > other.complexity;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const CodeElement& element);
};

int CodeElement::elementCounter = 0;

ostream& operator<<(ostream& os, const CodeElement& element) {
    os << element.type << "[" << element.elementId << "]: " << element.name 
       << " (CC: " << element.complexity << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: FUNCTION
// ==========================================

class Function : public CodeElement {
private:
    int parameters;
    int statements;
    vector<ControlStructure> controlStructures;
    static int functionCounter;

public:
    Function(string n, int params = 0, int stmts = 0) 
        : CodeElement(n, "Function"), parameters(params), statements(stmts) {
        functionCounter++;
    }

    ~Function() {
        functionCounter--;
    }

    // Override calculate complexity
    void calculateComplexity() override {
        complexity = 1; // Base complexity
        
        // Add complexity for control structures
        for (const auto& cs : controlStructures) {
            complexity += cs.getComplexity();
        }
        
        // Add complexity for parameters (simplified)
        if (parameters > 5) {
            complexity += (parameters - 5) / 2;
        }
    }

    // Override display
    void display() const override {
        CodeElement::display();
        cout << "Parameters: " << parameters << endl;
        cout << "Statements: " << statements << endl;
        cout << "Control Structures: " << controlStructures.size() << endl;
        
        if (!controlStructures.empty()) {
            cout << "Control Structures Details:" << endl;
            for (const auto& cs : controlStructures) {
                cout << "  ";
                cs.display();
            }
        }
    }

    // Add control structure
    void addControlStructure(const ControlStructure& cs) {
        controlStructures.push_back(cs);
        calculateComplexity(); // Recalculate complexity
    }

    // Remove control structure
    void removeControlStructure(string type) {
        auto it = find_if(controlStructures.begin(), controlStructures.end(),
            [type](const ControlStructure& cs) { return cs.getType() == type; });
        
        if (it != controlStructures.end()) {
            controlStructures.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Getters
    int getParameters() const { return parameters; }
    int getStatements() const { return statements; }
    int getControlStructureCount() const { return controlStructures.size(); }

    // Setters
    void setParameters(int p) { 
        if (p < 0) {
            throw ComplexityException("Parameters cannot be negative");
        }
        parameters = p; 
    }
    void setStatements(int s) { 
        if (s < 0) {
            throw ComplexityException("Statements cannot be negative");
        }
        statements = s; 
    }

    // Static function
    static int getFunctionCounter() { return functionCounter; }

    friend ostream& operator<<(ostream& os, const Function& func);
};

int Function::functionCounter = 0;

ostream& operator<<(ostream& os, const Function& func) {
    os << "Function[" << func.getElementId() << "]: " << func.getName() 
       << " (CC: " << func.getComplexity() << ", Params: " << func.parameters << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: CLASS
// ==========================================

class Class : public CodeElement {
private:
    int methods;
    int attributes;
    int inheritanceDepth;
    vector<shared_ptr<Function>> methodFunctions;
    static int classCounter;

public:
    Class(string n, int m = 0, int a = 0, int depth = 0) 
        : CodeElement(n, "Class"), methods(m), attributes(a), inheritanceDepth(depth) {
        classCounter++;
    }

    ~Class() {
        classCounter--;
    }

    // Override calculate complexity
    void calculateComplexity() override {
        complexity = 1; // Base complexity
        
        // Add complexity for methods
        complexity += methods * 2;
        
        // Add complexity for inheritance depth
        complexity += inheritanceDepth;
        
        // Add complexity from method functions
        for (const auto& func : methodFunctions) {
            complexity += func->getComplexity();
        }
    }

    // Override display
    void display() const override {
        CodeElement::display();
        cout << "Methods: " << methods << endl;
        cout << "Attributes: " << attributes << endl;
        cout << "Inheritance Depth: " << inheritanceDepth << endl;
        cout << "Method Functions: " << methodFunctions.size() << endl;
        
        if (!methodFunctions.empty()) {
            cout << "Method Functions Details:" << endl;
            for (const auto& func : methodFunctions) {
                cout << "  ";
                func->display();
            }
        }
    }

    // Add method function
    void addMethodFunction(shared_ptr<Function> func) {
        methodFunctions.push_back(func);
        calculateComplexity(); // Recalculate complexity
    }

    // Remove method function
    void removeMethodFunction(int functionId) {
        auto it = find_if(methodFunctions.begin(), methodFunctions.end(),
            [functionId](const shared_ptr<Function>& f) { 
                return f->getElementId() == functionId; 
            });
        
        if (it != methodFunctions.end()) {
            methodFunctions.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Getters
    int getMethods() const { return methods; }
    int getAttributes() const { return attributes; }
    int getInheritanceDepth() const { return inheritanceDepth; }
    int getMethodFunctionCount() const { return methodFunctions.size(); }

    // Setters
    void setMethods(int m) { 
        if (m < 0) {
            throw ComplexityException("Methods cannot be negative");
        }
        methods = m; 
    }
    void setAttributes(int a) { 
        if (a < 0) {
            throw ComplexityException("Attributes cannot be negative");
        }
        attributes = a; 
    }
    void setInheritanceDepth(int depth) { 
        if (depth < 0) {
            throw ComplexityException("Inheritance depth cannot be negative");
        }
        inheritanceDepth = depth; 
    }

    // Static function
    static int getClassCounter() { return classCounter; }

    friend ostream& operator<<(ostream& os, const Class& cls);
};

int Class::classCounter = 0;

ostream& operator<<(ostream& os, const Class& cls) {
    os << "Class[" << cls.getElementId() << "]: " << cls.getName() 
       << " (CC: " << cls.getComplexity() << ", Methods: " << cls.methods << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: MODULE
// ==========================================

class Module : public CodeElement {
private:
    vector<shared_ptr<Function>> functions;
    vector<shared_ptr<Class>> classes;
    vector<string> dependencies;
    static int moduleCounter;

public:
    Module(string n) : CodeElement(n, "Module") {
        moduleCounter++;
    }

    ~Module() {
        moduleCounter--;
    }

    // Override calculate complexity
    void calculateComplexity() override {
        complexity = 1; // Base complexity
        
        // Add complexity from functions
        for (const auto& func : functions) {
            complexity += func->getComplexity();
        }
        
        // Add complexity from classes
        for (const auto& cls : classes) {
            complexity += cls->getComplexity();
        }
        
        // Add complexity for dependencies
        complexity += dependencies.size();
    }

    // Override display
    void display() const override {
        CodeElement::display();
        cout << "Functions: " << functions.size() << endl;
        cout << "Classes: " << classes.size() << endl;
        cout << "Dependencies: " << dependencies.size() << endl;
        
        if (!dependencies.empty()) {
            cout << "Dependencies:" << endl;
            for (const auto& dep : dependencies) {
                cout << "  - " << dep << endl;
            }
        }
    }

    // Add function
    void addFunction(shared_ptr<Function> func) {
        functions.push_back(func);
        calculateComplexity(); // Recalculate complexity
    }

    // Add class
    void addClass(shared_ptr<Class> cls) {
        classes.push_back(cls);
        calculateComplexity(); // Recalculate complexity
    }

    // Add dependency
    void addDependency(string dep) {
        dependencies.push_back(dep);
        calculateComplexity(); // Recalculate complexity
    }

    // Remove function
    void removeFunction(int functionId) {
        auto it = find_if(functions.begin(), functions.end(),
            [functionId](const shared_ptr<Function>& f) { 
                return f->getElementId() == functionId; 
            });
        
        if (it != functions.end()) {
            functions.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Remove class
    void removeClass(int classId) {
        auto it = find_if(classes.begin(), classes.end(),
            [classId](const shared_ptr<Class>& c) { 
                return c->getElementId() == classId; 
            });
        
        if (it != classes.end()) {
            classes.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Remove dependency
    void removeDependency(string dep) {
        auto it = find(dependencies.begin(), dependencies.end(), dep);
        if (it != dependencies.end()) {
            dependencies.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Getters
    int getFunctionCount() const { return functions.size(); }
    int getClassCount() const { return classes.size(); }
    int getDependencyCount() const { return dependencies.size(); }

    // Static function
    static int getModuleCounter() { return moduleCounter; }

    friend ostream& operator<<(ostream& os, const Module& module);
};

int Module::moduleCounter = 0;

ostream& operator<<(ostream& os, const Module& module) {
    os << "Module[" << module.getElementId() << "]: " << module.getName() 
       << " (CC: " << module.getComplexity() << ", Functions: " << module.functions.size() 
       << ", Classes: " << module.classes.size() << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: PROJECT
// ==========================================

class Project : public CodeElement {
private:
    vector<shared_ptr<Module>> modules;
    int totalComplexity;
    static int projectCounter;

public:
    Project(string n) : CodeElement(n, "Project"), totalComplexity(0) {
        projectCounter++;
    }

    ~Project() {
        projectCounter--;
    }

    // Override calculate complexity
    void calculateComplexity() override {
        complexity = 1; // Base complexity
        totalComplexity = 0;
        
        // Calculate total complexity from all modules
        for (const auto& module : modules) {
            totalComplexity += module->getComplexity();
        }
        
        complexity = totalComplexity;
    }

    // Override display
    void display() const override {
        CodeElement::display();
        cout << "Modules: " << modules.size() << endl;
        cout << "Total Complexity: " << totalComplexity << endl;
        
        if (!modules.empty()) {
            cout << "Modules Details:" << endl;
            for (const auto& module : modules) {
                cout << "  ";
                module->display();
            }
        }
    }

    // Add module
    void addModule(shared_ptr<Module> module) {
        modules.push_back(module);
        calculateComplexity(); // Recalculate complexity
    }

    // Remove module
    void removeModule(int moduleId) {
        auto it = find_if(modules.begin(), modules.end(),
            [moduleId](const shared_ptr<Module>& m) { 
                return m->getElementId() == moduleId; 
            });
        
        if (it != modules.end()) {
            modules.erase(it);
            calculateComplexity(); // Recalculate complexity
        }
    }

    // Get average complexity
    double getAverageComplexity() const {
        if (modules.empty()) return 0.0;
        return (double)totalComplexity / modules.size();
    }

    // Get highest complexity module
    shared_ptr<Module> getHighestComplexityModule() const {
        if (modules.empty()) return nullptr;
        
        auto maxIt = max_element(modules.begin(), modules.end(),
            [](const shared_ptr<Module>& a, const shared_ptr<Module>& b) {
                return a->getComplexity() < b->getComplexity();
            });
        
        return *maxIt;
    }

    // Getters
    int getModuleCount() const { return modules.size(); }
    int getTotalComplexity() const { return totalComplexity; }

    // Static function
    static int getProjectCounter() { return projectCounter; }

    friend ostream& operator<<(ostream& os, const Project& project);
};

int Project::projectCounter = 0;

ostream& operator<<(ostream& os, const Project& project) {
    os << "Project[" << project.getElementId() << "]: " << project.getName() 
       << " (CC: " << project.getComplexity() << ", Modules: " << project.modules.size() << ")";
    return os;
}

// ==========================================
// COMPLEXITY CALCULATOR CLASS
// ==========================================

class ComplexityCalculator {
private:
    vector<string> analysisRules;
    int lowThreshold;
    int mediumThreshold;
    int highThreshold;
    static int calculatorCounter;

public:
    ComplexityCalculator(int low = 5, int medium = 10, int high = 15) 
        : lowThreshold(low), mediumThreshold(medium), highThreshold(high) {
        calculatorCounter++;
        
        // Initialize analysis rules
        analysisRules = {
            "Base complexity starts at 1",
            "Each control structure adds 1 to complexity",
            "Multiple parameters increase complexity",
            "Deep inheritance increases complexity",
            "High coupling increases complexity"
        };
    }

    ~ComplexityCalculator() {
        calculatorCounter--;
    }

    // Calculate complexity for function
    int calculateFunctionComplexity(const Function& func) {
        int complexity = 1; // Base complexity
        
        // Add complexity for control structures
        complexity += func.getControlStructureCount();
        
        // Add complexity for parameters
        if (func.getParameters() > 5) {
            complexity += (func.getParameters() - 5) / 2;
        }
        
        return complexity;
    }

    // Calculate complexity for class
    int calculateClassComplexity(const Class& cls) {
        int complexity = 1; // Base complexity
        
        // Add complexity for methods
        complexity += cls.getMethods() * 2;
        
        // Add complexity for inheritance depth
        complexity += cls.getInheritanceDepth();
        
        return complexity;
    }

    // Calculate complexity for module
    int calculateModuleComplexity(const Module& module) {
        int complexity = 1; // Base complexity
        
        // Add complexity from functions and classes
        complexity += module.getFunctionCount() + module.getClassCount();
        
        // Add complexity for dependencies
        complexity += module.getDependencyCount();
        
        return complexity;
    }

    // Analyze complexity level
    string analyzeComplexityLevel(int complexity) const {
        if (complexity <= lowThreshold) return "Low";
        else if (complexity <= mediumThreshold) return "Medium";
        else if (complexity <= highThreshold) return "High";
        else return "Very High";
    }

    // Generate refactoring recommendations
    vector<string> generateRecommendations(const CodeElement& element) {
        vector<string> recommendations;
        
        if (element.getComplexity() > highThreshold) {
            recommendations.push_back("Consider breaking down into smaller components");
            recommendations.push_back("Reduce number of control structures");
            recommendations.push_back("Simplify conditional logic");
        }
        
        if (element.getComplexity() > mediumThreshold) {
            recommendations.push_back("Consider extracting methods");
            recommendations.push_back("Reduce parameter count");
        }
        
        if (element.getType() == "Function" && element.getComplexity() > 10) {
            recommendations.push_back("Function is too complex - consider splitting");
        }
        
        if (element.getType() == "Class" && element.getComplexity() > 20) {
            recommendations.push_back("Class is too complex - consider inheritance or composition");
        }
        
        return recommendations;
    }

    // Display analysis rules
    void displayAnalysisRules() const {
        cout << "\n=== COMPLEXITY ANALYSIS RULES ===" << endl;
        for (size_t i = 0; i < analysisRules.size(); i++) {
            cout << (i + 1) << ". " << analysisRules[i] << endl;
        }
    }

    // Display thresholds
    void displayThresholds() const {
        cout << "\n=== COMPLEXITY THRESHOLDS ===" << endl;
        cout << "Low: <= " << lowThreshold << endl;
        cout << "Medium: " << (lowThreshold + 1) << " - " << mediumThreshold << endl;
        cout << "High: " << (mediumThreshold + 1) << " - " << highThreshold << endl;
        cout << "Very High: > " << highThreshold << endl;
    }

    // Getters
    int getLowThreshold() const { return lowThreshold; }
    int getMediumThreshold() const { return mediumThreshold; }
    int getHighThreshold() const { return highThreshold; }
    int getRuleCount() const { return analysisRules.size(); }

    // Setters
    void setLowThreshold(int low) { 
        if (low < 1) {
            throw ComplexityException("Low threshold must be at least 1");
        }
        lowThreshold = low; 
    }
    void setMediumThreshold(int medium) { 
        if (medium <= lowThreshold) {
            throw ComplexityException("Medium threshold must be greater than low threshold");
        }
        mediumThreshold = medium; 
    }
    void setHighThreshold(int high) { 
        if (high <= mediumThreshold) {
            throw ComplexityException("High threshold must be greater than medium threshold");
        }
        highThreshold = high; 
    }

    // Static function
    static int getCalculatorCounter() { return calculatorCounter; }

    // Operator overloading
    ComplexityCalculator& operator+=(const string& rule) {
        analysisRules.push_back(rule);
        return *this;
    }

    ComplexityCalculator& operator-=(const string& rule) {
        auto it = find(analysisRules.begin(), analysisRules.end(), rule);
        if (it != analysisRules.end()) {
            analysisRules.erase(it);
        }
        return *this;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const ComplexityCalculator& calc);
};

int ComplexityCalculator::calculatorCounter = 0;

ostream& operator<<(ostream& os, const ComplexityCalculator& calc) {
    os << "ComplexityCalculator: " << calc.analysisRules.size() << " rules, "
       << "Thresholds: " << calc.lowThreshold << "/" << calc.mediumThreshold << "/" << calc.highThreshold;
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class ComplexityManager {
private:
    vector<shared_ptr<T>> items;

public:
    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void removeItem(shared_ptr<T> item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void displayAll() {
        for (const auto& item : items) {
            item->display();
            cout << "------------------------" << endl;
        }
    }

    int getCount() const { return items.size(); }

    // Calculate total complexity
    int getTotalComplexity() const {
        int total = 0;
        for (const auto& item : items) {
            total += item->getComplexity();
        }
        return total;
    }

    // Get average complexity
    double getAverageComplexity() const {
        if (items.empty()) return 0.0;
        return (double)getTotalComplexity() / items.size();
    }
};

// ==========================================
// DEMONSTRATION FUNCTION
// ==========================================

void demonstrateComplexityAnalysis() {
    cout << "COMPUTE CC (CYCLOMATIC COMPLEXITY) SYSTEM DEMONSTRATION" << endl;
    cout << "=======================================================" << endl;

    ComplexityCalculator calculator(5, 10, 15);

    // Create functions with different complexities
    auto func1 = make_shared<Function>("calculateSum", 2, 5);
    func1->addControlStructure(ControlStructure("if", "x > 0"));
    func1->addControlStructure(ControlStructure("while", "i < n"));
    func1->calculateComplexity();

    auto func2 = make_shared<Function>("processData", 5, 15);
    func2->addControlStructure(ControlStructure("if", "data != null"));
    func2->addControlStructure(ControlStructure("for", "i = 0; i < size"));
    func2->addControlStructure(ControlStructure("switch", "type"));
    func2->addControlStructure(ControlStructure("case", "type1"));
    func2->addControlStructure(ControlStructure("case", "type2"));
    func2->calculateComplexity();

    auto func3 = make_shared<Function>("simpleFunction", 1, 3);
    func3->calculateComplexity();

    // Create classes
    auto class1 = make_shared<Class>("DataProcessor", 5, 10, 2);
    class1->addMethodFunction(func1);
    class1->addMethodFunction(func2);
    class1->calculateComplexity();

    auto class2 = make_shared<Class>("SimpleClass", 2, 3, 0);
    class2->addMethodFunction(func3);
    class2->calculateComplexity();

    // Create modules
    auto module1 = make_shared<Module>("CoreModule");
    module1->addFunction(func1);
    module1->addFunction(func2);
    module1->addClass(class1);
    module1->addDependency("DatabaseModule");
    module1->addDependency("UtilsModule");
    module1->calculateComplexity();

    auto module2 = make_shared<Module>("UtilsModule");
    module2->addFunction(func3);
    module2->addClass(class2);
    module2->calculateComplexity();

    // Create project
    auto project = make_shared<Project>("MyProject");
    project->addModule(module1);
    project->addModule(module2);
    project->calculateComplexity();

    // Display analysis rules and thresholds
    calculator.displayAnalysisRules();
    calculator.displayThresholds();

    // Display all elements
    cout << "\n=== ALL CODE ELEMENTS ===" << endl;
    func1->display();
    cout << "------------------------" << endl;
    func2->display();
    cout << "------------------------" << endl;
    func3->display();
    cout << "------------------------" << endl;
    class1->display();
    cout << "------------------------" << endl;
    class2->display();
    cout << "------------------------" << endl;
    module1->display();
    cout << "------------------------" << endl;
    module2->display();
    cout << "------------------------" << endl;
    project->display();

    // Generate recommendations
    cout << "\n=== REFACTORING RECOMMENDATIONS ===" << endl;
    vector<string> recommendations = calculator.generateRecommendations(*func2);
    cout << "For function 'processData':" << endl;
    for (const auto& rec : recommendations) {
        cout << "- " << rec << endl;
    }

    // Demonstrate operator overloading
    cout << "\n=== OPERATOR OVERLOADING DEMONSTRATIONS ===" << endl;
    
    // Comparison operators
    if (*func1 < *func2) {
        cout << "Function 1 has lower complexity than Function 2" << endl;
    }
    
    if (*class1 > *class2) {
        cout << "Class 1 has higher complexity than Class 2" << endl;
    }
    
    // Calculator operators
    calculator += "New analysis rule added";
    cout << "Calculator after adding rule: " << calculator << endl;

    // Project statistics
    cout << "\n=== PROJECT STATISTICS ===" << endl;
    cout << "Total Complexity: " << project->getTotalComplexity() << endl;
    cout << "Average Complexity: " << project->getAverageComplexity() << endl;
    
    auto highestModule = project->getHighestComplexityModule();
    if (highestModule) {
        cout << "Highest Complexity Module: " << highestModule->getName() 
             << " (CC: " << highestModule->getComplexity() << ")" << endl;
    }
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Element {
    static int count;
    int id;
public:
    Element() { id = ++count; cout << "Element" << id; }
    ~Element() { cout << "~Element" << id; }
};
int Element::count = 0;
int main() {
    Element e1, e2;
    { Element e3; }
    return 0;
}
Answer: Element1Element2Element3~Element3~Element2~Element1

Problem 2: What will be the output?
class Function {
    int complexity;
public:
    Function(int c = 1) : complexity(c) {}
    Function operator+(const Function& f) {
        return Function(complexity + f.complexity + 2);
    }
    friend ostream& operator<<(ostream& os, const Function& func) {
        return os << "CC:" << func.complexity;
    }
};
int main() {
    Function f1(3), f2(4);
    cout << f1 + f2;
    return 0;
}
Answer: CC:9

Problem 3: What will be the output?
class Calculator {
    int threshold;
public:
    Calculator(int t = 10) : threshold(t) {}
    Calculator operator+=(int val) {
        threshold += val + 1;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Calculator& calc) {
        return os << "Threshold:" << calc.threshold;
    }
};
int main() {
    Calculator calc(5);
    calc += 3;
    cout << calc;
    return 0;
}
Answer: Threshold:9
*/

int main() {
    demonstrateComplexityAnalysis();
    return 0;
} 
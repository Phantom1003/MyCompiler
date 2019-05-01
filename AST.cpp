#include <iostream>
#include <map>
#include <vector>
#include <llvm-c/IR/value.h>


class ASTNode {
private:
	int id;

public:
	static int idCnt;

	virtual ~ASTNode() = default;
	virtual llvm::Value * codeGen(CodeGenContext &context) {
		return 0;
	}
	virtual std::vector<ASTNode *> getChildren() = 0;
	virtual std::string getName() = 0;

	ASTNode(){
		id = ++idCnt;
	}
};

class Program : public ASTNode {
	ProgramHead * programHead = 0;
	Routine * routine = 0;

	Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {}
	
	std:vector<ASTNode *> getChildren() {
		auto ch = std:vector<ASTNode *>();
		ch.push_back(programHead);
		ch.push_back(routine);
		return ch;
	}


class ProgramHead : public ASTNode {
	std:string name;

	ProgramHead(std::string name) : name(std::move(name)) {}

	std:vector<ASTNode *> getChildren() {
		return std:vector<ASTNode *> ();
	}

	std::string getName() {
		return name;
	}
}
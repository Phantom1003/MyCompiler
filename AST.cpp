#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "llvm-c/IR/value.h"


int stoi(std::string s) {
	return std::stoi(s);
}

double stod(std::string s) {
	return std::stod(s);
}

std::string itos(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string dtos(double d) {
	std::stringstream ss;
	ss << d;
	return ss.str();
}

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
	ProgramHead * programHead;
	Routine * routine;

	explicit Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {}
	
	std:vector<ASTNode *> getChildren() override {
		auto ch = std:vector<ASTNode *>();
		ch.push_back(programHead);
		ch.push_back(routine);
		return ch;
	}

	~Program() {
		delete programHead;
		delete routine;
	}
};

class ProgramHead : public ASTNode {
	std:string name;

	explicit ProgramHead(std::string name) : name(std::move(name)) {}

	std:vector<ASTNode *> getChildren() override {
		return std:vector<ASTNode *> ();
	}

	std::string getName() {
		return name;
	}
};

class Routine : public ASTNode {
	RoutineHead * routineHead;
	RoutineBody * routineBody;

	explicit Routine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(routineHead);
		ch.push_back(routineBody);
		return ch;
	}
	~Routine() {
		delete routineHead;
		delete routineBody;
	}
};

class SubRoutine : public ASTNode {
	RoutineHead * routineHead{};
	RoutineBody * routineBody{};

	explicit SubRoutine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(routineHead);
		ch.push_back(routineBody);
		return ch;
	}
	~SubRoutine() {
		delete routineHead;
		delete routineBody;
	}
};

class RoutineHead : public ASTNode {
	LabelPart * labelPart;
	ConstPart * constPart;
	TypePart * typePart;
	VarPart * varPart;
	RoutinePart * routinePart;

	explicit RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart, RoutinePart *routinePart) : labelPart(labelPart), constPart(constPart), typePart(typePart), varPart(varPart), routinePart(routinePart) {}

	std::vector<ASTNode *> getChildren() override {
        auto ch = std::vector<ASTNode *>();
        ch.push_back(labelPart);
        ch.push_back(constPart);
        ch.push_back(typePart);
        ch.push_back(varPart);
        ch.push_back(routinePart);
        return ch;
    }
    ~RoutineHead() {
    	delete labelPart;
    	delete constPart;
    	delete typePart;
    	delete varPart;
    	delete routinePart;
    }
};

class LabelPart : public ASTNode {

	std::vector<ASTNode *> getChildren() override {
		return std::vector<ASTNode *>();
	}
};

class ConstPart : public ASTNode {
	ConstExprList * constExprList;

	explicit ConstPart(ConstExprList *constExprList) : constExprList(constExprList) {}
	explicit ConstPart() {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(constExprList)
			ch.push_back(constExprList);
		return ch;
	}
};

class ConstExprList : public ASTNode {
	ConstExprList * preList;
	ConstValue * constValue;

	explicit ConstExprList(std::string name, ConstExprList *preList, ConstValue * constValue) : name(std::move(name), preList(preList), constValue(constValue)) {}

	explicit ConstExprList(std::string name, ConstValue * constValue) : name(std::move(name)), constValue(constValue) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(constValue);
		return ch;
	}
};

class ConstValue : public ASTNode {
	int token;
	std::string value;

	explicit ConstValue(int token, std::string value) : token(token), value(std::move(value)) {}

	std::vector<ASTNode *> getChildren() override {
		return std::vector<ASTNode *>();
	}

	ConstValue * neg() {
		if(token == INTEGER) {
			return new ConstValue(INTEGER, itos(-stoi(value)));
		}
		else if(token == REAL) {
			return new ConstValue(REAL, dtos(-stod(value)));
		}
		else {
			return new ConstValue(token, value);
		}
	}
};

class TypePart : public ASTNode {
	TypeDeclList * typeDeclList;

	explicit TypePart(TypeDeclList * typeDeclList) : typeDeclList(typeDeclList) {}

	explicit TypePart() {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(typeDeclList);
		return ch;
	}
};

class TypeDeclList : public ASTNode {
	TypeDeclList * preList;
	TypeDefinition * typeDefinition;

	explicit TypeDeclList(TypeDeclList * preList, TypeDefinition * typeDefinition) : preList(preList), typeDefinition(typeDefinition) {}
	
	explicit TypeDeclList(TypeDefinition * typeDefinition) : typeDefinition(typeDefinition) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(typeDefinition);
		return ch;
	}
};

class TypeDefinition : public ASTNode {
	std::string name;
	TypeDecl * typeDecl;

	explicit TypeDefinition(std::string name, TypeDecl * typeDecl) : name(std::move(name)), typeDecl(typeDecl) {}
	
	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(typeDecl);
		return ch;
	}

	std::string getName() override {
		return std::move(name);
	}

};

class TypeDecl : public ASTNode {
	SimpleTypeDecl * simpleTypeDecl{};
	ArrayTypeDecl * arrayTypeDecl{};
	RecordTypeDecl * recordTypeDecl{};

	explicit TypeDecl(SimpleTypeDecl * simpleTypeDecl) : simpleTypeDecl(simpleTypeDecl) {}

	explicit TypeDecl(ArrayTypeDecl * arrayTypeDecl) : arrayTypeDecl(arrayTypeDecl) {}
	
	explicit TypeDecl(RecordTypeDecl * recordTypeDecl) : recordTypeDecl(recordTypeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(simpleTypeDecl)
			ch.push_back(simpleTypeDecl);
		if(arrayTypeDecl)
			ch.push_back(arrayTypeDecl);
		if(recordTypeDecl)
			ch.push_back(recordTypeDecl);
		return ch;
	}

	~TypeDecl() {
		delete simpleTypeDecl;
		delete arrayTypeDecl;
		delete recordTypeDecl;
	}
};

class SimpleTypeDecl : public ASTNode {
	std::string sysType;
	std::string name;

	NameList * nameList;
	ConstValue * lowerValue, upperValue;
	std::string lowerName, upperName

	explicit SimpleTypeDecl(int token, string value) {
		if(token == SYS_TYPE)
			sysType = std::move(value);
		if(token == NAME)
			name = std::move(value);
	}

	explicit SimpleTypeDecl(NameList * nameList) : nameList(nameList);

	explicit SimpleTypeDecl(ConstValue * lowerValue, ConstValue * upperValue) : lowerValue(lowerValue), upperValue(upperValue) {}

	explicit SimpleTypeDecl(std::string lowerName, std::string upperName) : lowerName(std::move(lowerName)), upperName(std::move(upperName)) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(nameList)
			ch.push_back(nameList);
		if(lowerValue && upperValue){
			ch.push_back(lowerValue);
			ch.push_back(upperValue);
		}
		return ch;
	}
	~SimpleTypeDecl() {
		delete nameList;
		delete lowerValue;
		delete upperValue;
	}
};

class ArrayTypeDecl : public ASTNode {
	SimpleTypeDecl * simpleTypeDecl;
	TypeDecl * typeDecl;

	explicit ArrayTypeDecl(SimpleTypeDecl * simpleTypeDecl, TypeDecl * typeDecl) : simpleTypeDecl(simpleTypeDecl), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(simpleTypeDecl);
		ch.push_back(typeDecl);
		return ch;
	}

	~ArrayTypeDecl() {
		delete simpleTypeDecl;
		delete typeDecl;
	}
};

class RecordTypeDecl : public ASTNode {
	FieldDeclList * fieldDeclList;

	explicit RecordTypeDecl(FieldDeclList * fieldDeclList) : fieldDeclList(fieldDeclList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(fieldDeclList);
		return ch;
	}

	~RecordTypeDecl() {
		delete fieldDeclList;
	}
};

class FieldDeclList : fieldDeclList {
	FieldDeclList * preList;
	FieldDecl * fieldDecl;

	explicit FieldDeclList(FieldDeclList * fieldDeclList, FieldDecl * fieldDecl) : fieldDeclList(fieldDeclList), fieldDecl(fieldDecl) {}

	explicit FieldDeclList(FieldDecl * fieldDecl) : fieldDecl(fieldDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(fieldDeclList)
			ch.push_back(fieldDeclList);
		ch.push_back(fieldDecl);
		return ch;
	}

	~FieldDeclList() {
		delete preList;
		delete fieldDecl;
	}
};

class FieldDecl : public ASTNode {
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit FieldDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(nameList);
		ch.push_back(typeDecl);
		return ch;
	}

	~FieldDecl() {
		delete nameList;
		delete typeDecl;
	}
};

class NameList : public ASTNode {
	NameList * preList;
	std::string name;

	explicit NameList(std::string name, NameList * nameList) : name(std::move(name)), nameList(nameList) {}

	explicit NameList(std::string name) : name(std::move(name)) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(preList);
		return ch;
	}

	std::string getName() {
		return std::move(name);
	}

	~NameList() {
		delete preList;
	}
};

class VarPart : public ASTNode {
	VarDeclList * varDeclList;

	explicit VarPart(VarDeclList * varDeclList) : varDeclList(varDeclList) {}

	explicit VarPart() : {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(varDeclList);
		return ch;
	}

	~VarPart() {
		delete varDeclList;
	}
};

class VarDeclList : public ASTNode {
	VarDeclList * preList;
	VarDecl * varDecl;

	explicit VarDeclList(VarDeclList * preList, VarDecl * varDecl) : preList(preList), varDecl(varDecl) {}

	explicit VarDeclList(VarDecl * varDecl) : varDecl(varDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(varDecl);
		return ch;
	}

	~VarDeclList() {
		delete preList;
		delete varDecl;
	}
};

class VarDecl : public ASTNode {
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit VarDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(nameList);
		ch.push_back(typeDecl);
		return ch;
	}

	~VarDecl() {
		delete nameList;
		delete typeDecl;
	}
};

class RoutinePart : public ASTNode {
	RoutinePart * prePart;
	FunctionDecl * functionDecl;
	ProcedureDecl * procedureDecl;

	explicit RoutinePart(RoutinePart * prePart, FunctionDecl * functionDecl) : prePart(prePart), functionDecl(functionDecl) {}

	explicit RoutinePart(RoutinePart * prePart, ProcedureDecl * procedureDecl) : prePart(prePart), procedureDecl(procedureDecl) {}

	explicit RoutinePart(FunctionDecl * functionDecl) : functionDecl(functionDecl) {}

	explicit RoutinePart(ProcedureDecl * procedureDecl) : procedureDecl(procedureDecl) {}

	explicit RoutinePart() : {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(prePart)
			ch.push_back(prePart);
		if(funcitonDecl)
			ch.push_back(functionDecl);
		if(procedureDecl)
			ch.push_back(procedureDecl);
		return ch;
	}

	~RoutinePart() {
		delete prePart;
		delete functionDecl;
		delete procedureDecl;
	}
};

class FunctionDecl : public ASTNode {
	FunctionHead * functionHead;
	SubRoutine * subRoutine;

	explicit FunctionDecl(FunctionHead * functionHead, SubRoutine * subRoutine) : functionHead(functionHead), subRoutine(subRoutine) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(functionHead);
		ch.push_back(subRoutine);
		return ch;
	}

	~FunctionDecl() {
		delete functionHead;
		delete subRoutine;
	}
};

class FunctionHead : public ASTNode {
	std::string name;
	Parameters * parameters;
	SimpleTypeDecl * simpleTypeDecl;

	explicit FunctionHead(std::string name, Parameters * parameters, SimpleTypeDecl * simpleTypeDecl) : name(name), parameters(parameters), simpleTypeDecl(simpleTypeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(parameters);
		ch.push_back(simpleTypeDecl);
		return ch;
	}

	std::string getName() {
		return std::move(name);
	}

	~FunctionHead() {
		delete parameters;
		delete simpleTypeDecl;
	}
};

class ProcedureDecl : public ASTNode {
	ProcedureHead * procedureHead;
	SubRoutine * subRoutine;

	explicit ProcedureDecl(ProcedureHead * procedureHead, SubRoutine * subRoutine) : procedureHead(procedureHead), subRoutine(subRoutine) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(procedureHead);
		ch.push_back(subRoutine);
		return ch;
	}

	~ProcedureDecl() {
		delete procedureHead;
		delete subRoutine;
	}
};

class ProcedureHead : public ASTNode {
	Parameters * parameters;
	std::string name;

	explicit ProcedureHead(std::string name, Parameters * parameters) : name(std::move(name)), parameters(parameters) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(parameters);
		return ch;
	}

	~ProcedureHead() {
		delete parameters;
	}
};

class Parameters : public ASTNode {
	ParaDeclList * paraDeclList;

	explicit Parameters(ParaDeclList * paraDeclList) : paraDeclList(paraDeclList) {}
	explicit Parameters() {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(paraDeclList)
			ch.push_back(paraDeclList);
		return ch;
	}

	~Parameters() {
		delete paraDeclList;
	}
};

class ParaDeclList : public ASTNode {
	ParaDeclList * preList;
	ParaTypeList * paraTypeList;

	explicit ParaDeclList(ParaDeclList * preList, ParaTypeList * paraTypeList) : preList(preList), paraTypeList(paraTypeList) {}

	explicit ParaDeclList(ParaTypeList * paraTypeList) : paraTypeList(paraTypeList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(paraTypeList);
		return ch;
	}
};

class ParaTypeList : public ASTNode {
	VarParaList * varParaList;
	ValParaList * valParaList;
	SimpleTypeDecl * simpleTypeDecl;

	explicit ParaTypeList(VarParaList * varParaList, SimpleTypeDecl * simpleTypeDecl) : varParaList(varParaList), simpleTypeDecl(simpleTypeDecl) {}

	explicit ParaTypeList(ValParaList * valParaList, SimpleTypeDecl * simpleTypeDecl) : valParaList(ValParaList), simpleTypeDecl(simpleTypeDecl) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(varParaList)
			ch.push_back(varParaList);
		if(valParaList)
			ch.push_back(valTypeList);
		ch.push_back(simpleTypeDecl);
		return ch;
	}

	~ParaTypeList() {
		delete varParaList;
		delete valParaList;
	}
};

class VarParaList : public ASTNode {
	NameList * nameList;

	explicit VarParaList(NameList * nameList) : nameList(nameList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(nameList);
		return ch;
	}

	~VarParaList() {
		delete nameList;
	}
};

class ValParaList : public ASTNode {
	NameList * nameList;

	explicit ValParaList(NameList * nameList) : nameList(nameList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(nameList);
		return ch;
	}

	~ValParaList() {
		delete nameList;
	}
};

class RoutineBody : public ASTNode {
	CompoundStmt * compoundStmt;

	explicit RoutineBody(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(compoundStmt);
		return ch;
	}

	~RoutineBody() {
		delete compoundStmt;
	}
};

class CompoundStmt : public ASTNode {
	StmtList * stmtList;

	explicit CompoundStmt(StmtList * stmtList) : stmtList(stmtList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(stmtList);
		return ch;
	}

	~CompoundStmt() {
		delete stmtList;
	}
};

class StmtList : public ASTNode {
	StmtList * preList;
	Stmt * stmt;

	explicit StmtList(StmtList * preList, Stmt * stmt) : preList(preList), stmt(stmt) {}

	explicit StmtList(Stmt * stmt) : stmt(stmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(stmt);
		return ch;
	}

	~StmtList() {
		delete preList;
		delete stmt;
	}
};

class Stmt : public ASTNode {
	std::string label;
	NonLabelStmt * nonLabelStmt;

	explicit Stmt(std::string label, NonLabelStmt * nonLabelStmt) : label(std::move(label)), nonLabelStmt(nonLabelStmt) {}

	explicit Stmt(NonLabelStmt * nonLabelStmt) : nonLabelStmt(nonLabelStmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(nonLabelStmt);
		return ch;
	}

	~Stmt() {
		delete nonLabelStmt;
	}
};

class NonLabelStmt : public ASTNode {
	AssignStmt * assignStmt;
	ProcStmt * procStmt;
	CompoundStmt * compoundStmt;
	IfStmt * ifStmt;
	RepeatStmt * repeatStmt;
	WhileStmt * whileStmt;
	ForStmt * forStmt;
	CaseStmt * caseStmt;
	GotoStmt * gotoStmt;

	explicit NonLabelStmt(AssignStmt * assignStmt) : assignStmt(assignStmt) {}

	explicit NonLabelStmt(ProcStmt * procStmt) : procStmt(procStmt) {}
	
	explicit NonLabelStmt(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}
	
	explicit NonLabelStmt(IfStmt * ifStmt) : ifStmt(ifStmt) {}
	
	explicit NonLabelStmt(RepeatStmt * repeatStmt) : repeatStmt(repeatStmt) {}
	
	explicit NonLabelStmt(WhileStmt * whileStmt) : whileStmt(whileStmt) {}
	
	explicit NonLabelStmt(ForStmt * forStmt) : forStmt(forStmt) {}
	
	explicit NonLabelStmt(CaseStmt * caseStmt) : caseStmt(caseStmt) {}
	
	explicit NonLabelStmt(GotoStmt * gotoStmt) : gotoStmt(gotoStmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(assignStmt)
			ch.push_back(assignStmt);
		if(procStmt)
			ch.push_back(procStmt);
		if(compoundStmt)
			ch.push_back(compoundStmt);
		if(ifStmt)
			ch.push_back(ifStmt);
		if(repeatStmt)
			ch.push_back(repeatStmt);
		if(whileStmt)
			ch.push_back(whileStmt);
		if(forStmt)
			ch.push_back(forStmt);
		if(caseStmt)
			ch.push_back(caseStmt);
		if(gotoStmt)
			ch.push_back(gotoStmt);
		return ch;
	}
	
	~NonLabelStmt() {
		delete assignStmt;
		delete procStmt;
		delete compoundStmt;
		delete ifStmt;
		delete repeatStmt;
		delete whileStmt;
		delete forStmt;
		delete caseStmt;
		delete gotoStmt;
	}
};

class AssignStmt : public ASTNode {
	std::string name, attr;
	Expression * expression, index;

	explicit AssignStmt(std::string name, Expression * expression) : name(std::move(name)), expression(express) {}

	explicit AssignStmt(std::string name, Expression * index, Expression * expression) : name(std::move(name)), index(index), expression(expression) {}

	explicit AssignStmt(std::string name, std::string attr, Expression * expression) : name(std::move(name)), attr(std::name(attr)), expression(expression) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(index)
			ch.push_back(index);
		ch.push_back(expression);
		return ch;
	}

	~AssignStmt() {
		delete expression;
		delete index;
	}
};

class ProcStmt : public ASTNode {
	std::string name, sysProc;
	ArgsList * ArgsList;
	ExpressionList * expressionList;
	Factor * factor;

	explicit ProcStmt(bool isSysProc, std::string val) {
		if(!isSysProc)
			name = std::move(val);
		else
			sysProc = std::move(val);
	}

	explicit ProcStmt(std::string name, ArgsList * argsList) : name(std::move(name)), argsList(argsList) {}

	explicit ProcStmt(std::string sysProc, ExpressionList * expressionList) : sysProc(std::move(sysProc)), expressionList(expressionList) {}

	explicit ProcStmt(Factor * factor) : factor(factor) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(argsList)
			ch.push_back(argsList);
		if(expressionList)
			ch.push_back(expressionList);
		if(factor)
			ch.push_back(factor);
		return ch;
	}

	~ProcStmt() {
		delete argsList;
		delete expressionList;
		delete factor;
	}
};

class IfStmt : public ASTNode {
	Expression * expression;
	Stmt * stmt;
	ElseClause * elseClause;

	explicit IfStmt(Expression * expression, Stmt * stmt, ElseClause * elseClause) : expression(expression), stmt(stmt), elseClause(elseClause) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(expression);
		ch.push_back(stmt);
		ch.push_back(elseClause);
		return ch;
	}

	~IfStmt() {
		delete expression;
		delete stmt;
		delete elseClause;
	}
};

class ElseClause : public ASTNode {
	Stmt * stmt;

	explicit ElseClause(Stmt * stmt) : stmt(stmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(stmt);
		return ch;
	}

	~ElseClause() {
		delete stmt;
	}
};

class RepeatStmt : public ASTNode {
	StmtList * stmtList;
	Expression * expression;

	explicit WhileStmt(StmtList * stmtList, Expression * expression) : stmtList(stmtList), expression(expression) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(stmtList);
		ch.push_back(expression);
		return ch;
	}

	~RepeatStmt() {
		delete stmtList;
	}
};

class WhileStmt : public ASTNode {
	Expression * expression;

	explicit WhileStmt(Expression * expression, Stmt * stmt) : expression(expression), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(expression);
		ch.push_back(stmt);
		return ch;
	}

	~WhileStmt() {
		delete expression;
		delete stmt;
	}
};

class ForStmt : public ASTNode {
	std::string name;
	Expression * expr1, expr2;
	Direction * direction;
	Stmt * stmt;

	explicit ForStmt(std::string name, Expression * expr1, Direction * direction, Expression * expr2, Stmt * stmt) : name(std::move(name)), expr1(expr1), direction(direction), expr2(expr2), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(expr1);
		ch.push_back(direction);
		ch.push_back(expr2);
		ch.push_back(stmt);
		return ch;
	}

	~ForStmt() {
		delete expr1;
		delete expr2;
		delete direction;
		delete stmt;
	}
};

class Direction : public ASTNode {
	std::string dir;

	explicit Direction(std::string dir) : dir(std::move(dir)) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		return ch;
	}
};

class CaseStmt : public ASTNode {
	Expression * expression;
	CaseExprList * caseExprList;

	explicit CaseStmt(Expression * expression, CaseExprList * caseExprList) : expression(expression), caseExprList(caseExprList) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(expression);
		ch.push_back(caseExprList);
		return ch;
	}

	~CaseStmt() {
		delete expression;
		delete caseExprList;
	}
};

class CaseExprList : public ASTNode {
	CaseExprList * preList;
	CaseExpr * caseExpr;

	explicit CaseExprList(CaseExprList * preList, CaseExpr * caseExpr) : preList(preList), caseExpr(caseExpr) {}

	explicit CaseExprList(CaseExpr * caseExpr) : caseExpr(caseExpr) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(caseExpr);
		return ch;
	}

	~CaseExprList() {
		delete preList;
		delete caseExpr;
	}
};

class CaseExpr : public ASTNode {
	std::string name;
	ConstValue * constValue;
	Stmt * stmt;

	explicit CaseExpr(ConstValue * constValue, Stmt * stmt) : constValue(constValue), stmt(stmt) {}

	explicit CaseExpr(std:string name, Stmt * stmt) : name(std::move(name)), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(constValue)
			ch.push_back(constValue);
		ch.push_back(stmt)
		return ch;
	}

	~CaseExpr() {
		delete constValue;
		delete stmt;
	}
};

class GotoStmt : public ASTNode {
	ConstValue * address;

	explicit GotoStmt(ConstValue * address) : address(new ConstValue(INTEGER, address)) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(address);
		return ch;
	}

	~GotoStmt() {
		delete address;
	}
};

class ExpressionList : public ASTNode {
	ExpressionList * preList;
	Expression * expression;

	explicit ExpressionList(ExpressionList * preList, Expression * expression) : preList(preList), expression(expression) {}

	explicit ExpressionList

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(preList);
		ch.push_back(expression);
		return ch;
	}

	~ExpressionList() {
		delete expressionList;
		delete expression;
	}
};

class Expression : public ASTNode {
	std::string binop;
	Expression * expression;
	Expr * expr;

	explicit Expression(std::string binop, Expression * expression, Expr * expr) : binop(std::move(binop)), expression(expression), expr(expr) {}

	explicit Expression(Expr * expr) : expr(expr) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(expression)
			ch.push_back(expression);
		ch.push_back(expr);
		return ch;
	}

	~Expression() {
		delete expression;
		delete expr;
	}
};

class Expr : public ASTNode {
	std::string binop;
	Expr * expr;
	Term * term;

	explicit Expr(std::string binop, Expr * expr, Term * term) : binop(std::move(binop)), expr(expr), term(term) {}

	explicit Expr(Term * term) : term(term) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(expr)
			ch.push_back(expr);
		ch.push_back(term);
		return ch;
	}

	~Expr() {
		delete expr;
		delete term;
	}
};
class Factor : public ASTNode {
	std::string name, attr, sysFunc;
	ArgsList * argsList;
	ConstValue * constValue;
	Expression * expression;
	Factor * factor;
	bool isMinus, inv = 0;

	explicit Factor(std::string name) : name(std::move(name)) {}

	explicit Factor(std::string name, ArgsList * argsList) : name(std::move(name)), argsList(argsList) {}

	explicit Factor(std::string sysFunc) : sysFunc(std::move(sysFunc)) {}

	explicit Factor(std::string sysFunc, ArgsList * argsList) : sysFunc(std::move(sysFunc)), argsList(argsList) {}

	explicit Factor(ConstValue * constValue) : constValue(constValue) {}

	explicit Factor(Expression * expression) : expression(expression) {}

	explicit Factor(int token, Factor * factor) : factor(factor) {
		if(token == NOT){
			isMinus = 0;
			inv = 1;
		} else if (token == MINUS) {
			isMinus = 1;
			inv = 1;
		}
	}

	explicit Factor(std::string name, Expression * expression) : name(std::move(name)), expression(expression) {}

	explicit Factor(std::string name, std::string attr) : name(std::move(name)), attr(std::move(attr)) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		ch.push_back(argsList);
		ch.push_back(constValue);
		ch.push_back(expression);
		ch.push_back(factor);
		return ch;
	}

	~Factor() {
		delete argsList;
		delete constValue;
		delete expression;
		delete factor;
	}
};

class ArgsList : public ASTNode {
	ArgsList * preList;
	Expression * expression;

	explicit ArgsList(ArgsList * preList, Expression * expression) : preList(preList), expression(expression) {}

	explicit ArgsList(Expression * expression) : expression(expression) {}

	std::vector<ASTNode *> getChildren() override {
		auto ch = std::vector<ASTNode *>();
		if(preList)
			ch.push_back(preList);
		ch.push_back(expression)
		return ch;
	}

	~ArgsList() {
		delete preList;
		delete expression;
	}
};
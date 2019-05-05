#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AST.hpp"
#include <sstream>

int s2i(std::string s) {
	return std::stoi(s);
}

double s2d(std::string s) {
	return std::stod(s);
}

std::string i2s(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string d2s(double d) {
	std::stringstream ss;
	ss << d;
	return ss.str();
}

int ASTNode::idCnt = 0;

ASTNode::ASTNode(){
	id = idCnt ++;
	std::cout << "Node Id:" << id << std::endl;
};
// virtual llvm::Value * codeGen(CodeGenContext &context) {
// 	return 0;
// }
// std::vector<ASTNode *> ASTNode::getChildren() {return std::vector<ASTNode *>();};
// std::string ASTNode::getName() { return "";};
// ASTNode::~ASTNode() {}


Program::Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {}

std::vector<ASTNode *> Program::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(programHead);
	ch.push_back(routine);
	return ch;
}

Program::~Program() {
	delete programHead;
	delete routine;
}

ProgramHead::ProgramHead(std::string name) : name(std::move(name)) {}

std::vector<ASTNode *> ProgramHead::getChildren() {
	return std::vector<ASTNode *> ();
}

std::string ProgramHead::getName(){
	return name;
}


Routine::Routine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

std::vector<ASTNode *> Routine::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(routineHead);
	ch.push_back(routineBody);
	return ch;
}

Routine::~Routine() {
	delete routineHead;
	delete routineBody;
}


SubRoutine::SubRoutine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

std::vector<ASTNode *> SubRoutine::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(routineHead);
	ch.push_back(routineBody);
	return ch;
}

SubRoutine::~SubRoutine() {
	delete routineHead;
	delete routineBody;
}

RoutineHead::RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart, RoutinePart *routinePart) : labelPart(labelPart), constPart(constPart), typePart(typePart), varPart(varPart), routinePart(routinePart) {}

std::vector<ASTNode *> RoutineHead::getChildren() {
    std::vector<ASTNode *> ch = std::vector<ASTNode *>();
    ch.push_back(labelPart);
    ch.push_back(constPart);
    ch.push_back(typePart);
    ch.push_back(varPart);
    ch.push_back(routinePart);
    return ch;
}
RoutineHead::~RoutineHead() {
	delete labelPart;
	delete constPart;
	delete typePart;
	delete varPart;
	delete routinePart;
}



std::vector<ASTNode *> LabelPart::getChildren() {
	return std::vector<ASTNode *>();
}


ConstPart::ConstPart(ConstExprList *constExprList) : constExprList(constExprList) {}
ConstPart::ConstPart() {}

std::vector<ASTNode *> ConstPart::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(constExprList)
		ch.push_back(constExprList);
	return ch;
}

ConstPart::~ConstPart() {
	delete constExprList;
}

ConstExprList::ConstExprList(std::string name, ConstExprList *preList, ConstValue * constValue) : name(std::move(name)), preList(preList), constValue(constValue) {}

ConstExprList::ConstExprList(std::string name, ConstValue * constValue) : name(std::move(name)), constValue(constValue) {}

std::vector<ASTNode *> ConstExprList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(constValue);
	return ch;
}
ConstExprList::~ConstExprList() {
	delete preList;
	delete constValue;
}

ConstValue::ConstValue(int token, std::string value) : token(token), value(std::move(value)) {}

std::vector<ASTNode *> ConstValue::getChildren() {
	return std::vector<ASTNode *>();
}

ConstValue * ConstValue::neg() {
	if(token == 286) {
		return new ConstValue(286, i2s(-s2i(value)));
	}
	else if(token == 287) {
		return new ConstValue(287, d2s(-s2d(value)));
	}
	else {
		return new ConstValue(token, value);
	}
}


TypePart::TypePart(TypeDeclList * typeDeclList) : typeDeclList(typeDeclList) {}

TypePart::TypePart() {}

std::vector<ASTNode *> TypePart::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(typeDeclList);
	return ch;
}


TypeDeclList::TypeDeclList(TypeDeclList * preList, TypeDefinition * typeDefinition) : preList(preList), typeDefinition(typeDefinition) {}
	
TypeDeclList::TypeDeclList(TypeDefinition * typeDefinition) : typeDefinition(typeDefinition) {}

std::vector<ASTNode *> TypeDeclList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(typeDefinition);
	return ch;
}


TypeDefinition::TypeDefinition(std::string name, TypeDecl * typeDecl) : name(std::move(name)), typeDecl(typeDecl) {}
	
std::vector<ASTNode *> TypeDefinition::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(typeDecl);
	return ch;
}

std::string TypeDefinition::getName() {
	return std::move(name);
}


TypeDecl::TypeDecl(SimpleTypeDecl * simpleTypeDecl) : simpleTypeDecl(simpleTypeDecl) {}

TypeDecl::TypeDecl(ArrayTypeDecl * arrayTypeDecl) : arrayTypeDecl(arrayTypeDecl) {}

TypeDecl::TypeDecl(RecordTypeDecl * recordTypeDecl) : recordTypeDecl(recordTypeDecl) {}

std::vector<ASTNode *> TypeDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(simpleTypeDecl)
		ch.push_back(simpleTypeDecl);
	if(arrayTypeDecl)
		ch.push_back(arrayTypeDecl);
	if(recordTypeDecl)
		ch.push_back(recordTypeDecl);
	return ch;
}

TypeDecl::~TypeDecl() {
	delete simpleTypeDecl;
	delete arrayTypeDecl;
	delete recordTypeDecl;
}


SimpleTypeDecl::SimpleTypeDecl(int token, std::string value) {
	if(token == 284)
		sysType = std::move(value);
	if(token == 258)
		name = std::move(value);
}

SimpleTypeDecl::SimpleTypeDecl(NameList * nameList) : nameList(nameList) {}

SimpleTypeDecl::SimpleTypeDecl(ConstValue * lowerValue, ConstValue * upperValue) : lowerValue(lowerValue), upperValue(upperValue) {}

SimpleTypeDecl::SimpleTypeDecl(std::string lowerName, std::string upperName) : lowerName(std::move(lowerName)), upperName(std::move(upperName)) {}

std::vector<ASTNode *> SimpleTypeDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(nameList)
		ch.push_back(nameList);
	if(lowerValue && upperValue){
		ch.push_back(lowerValue);
		ch.push_back(upperValue);
	}
	return ch;
}
SimpleTypeDecl::~SimpleTypeDecl() {
	delete nameList;
	delete lowerValue;
	delete upperValue;
}


ArrayTypeDecl::ArrayTypeDecl(SimpleTypeDecl * simpleTypeDecl, TypeDecl * typeDecl) : simpleTypeDecl(simpleTypeDecl), typeDecl(typeDecl) {}

std::vector<ASTNode *> ArrayTypeDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(simpleTypeDecl);
	ch.push_back(typeDecl);
	return ch;
}

ArrayTypeDecl::~ArrayTypeDecl() {
	delete simpleTypeDecl;
	delete typeDecl;
}


RecordTypeDecl::RecordTypeDecl(FieldDeclList * fieldDeclList) : fieldDeclList(fieldDeclList) {}

std::vector<ASTNode *> RecordTypeDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(fieldDeclList);
	return ch;
}

RecordTypeDecl::~RecordTypeDecl() {
	delete fieldDeclList;
}


FieldDeclList::FieldDeclList(FieldDeclList * preList, FieldDecl * fieldDecl) : preList(preList), fieldDecl(fieldDecl) {}

FieldDeclList::FieldDeclList(FieldDecl * fieldDecl) : fieldDecl(fieldDecl) {}

std::vector<ASTNode *> FieldDeclList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(fieldDecl);
	return ch;
}

FieldDeclList::~FieldDeclList() {
	delete preList;
	delete fieldDecl;
}


FieldDecl::FieldDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

std::vector<ASTNode *> FieldDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(nameList);
	ch.push_back(typeDecl);
	return ch;
}

FieldDecl::~FieldDecl() {
	delete nameList;
	delete typeDecl;
}


NameList::NameList(std::string name, NameList * preList) : name(std::move(name)), preList(preList) {}

NameList::NameList(std::string name) : name(std::move(name)) {}

std::vector<ASTNode *> NameList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(preList);
	return ch;
}

std::string NameList::getName() {
	return std::move(name);
}

NameList::~NameList() {
	delete preList;
}


VarPart::VarPart(VarDeclList * varDeclList) : varDeclList(varDeclList) {}

VarPart::VarPart(){}

std::vector<ASTNode *> VarPart::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(varDeclList);
	return ch;
}

VarPart::~VarPart() {
	delete varDeclList;
}


VarDeclList::VarDeclList(VarDeclList * preList, VarDecl * varDecl) : preList(preList), varDecl(varDecl) {}

VarDeclList::VarDeclList(VarDecl * varDecl) : varDecl(varDecl) {}

std::vector<ASTNode *> VarDeclList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(varDecl);
	return ch;
}

VarDeclList::~VarDeclList() {
	delete preList;
	delete varDecl;
}

VarDecl::VarDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

std::vector<ASTNode *> VarDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(nameList);
	ch.push_back(typeDecl);
	return ch;
}

VarDecl::~VarDecl() {
	delete nameList;
	delete typeDecl;
}


RoutinePart::RoutinePart(RoutinePart * prePart, FunctionDecl * functionDecl) : prePart(prePart), functionDecl(functionDecl) {}

RoutinePart::RoutinePart(RoutinePart * prePart, ProcedureDecl * procedureDecl) : prePart(prePart), procedureDecl(procedureDecl) {}

RoutinePart::RoutinePart(FunctionDecl * functionDecl) : functionDecl(functionDecl) {}

RoutinePart::RoutinePart(ProcedureDecl * procedureDecl) : procedureDecl(procedureDecl) {}

RoutinePart::RoutinePart() {}

std::vector<ASTNode *> RoutinePart::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(prePart)
		ch.push_back(prePart);
	if(functionDecl)
		ch.push_back(functionDecl);
	if(procedureDecl)
		ch.push_back(procedureDecl);
	return ch;
}

RoutinePart::~RoutinePart() {
	delete prePart;
	delete functionDecl;
	delete procedureDecl;
}


FunctionDecl::FunctionDecl(FunctionHead * functionHead, SubRoutine * subRoutine) : functionHead(functionHead), subRoutine(subRoutine) {}

std::vector<ASTNode *> FunctionDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(functionHead);
	ch.push_back(subRoutine);
	return ch;
	}

FunctionDecl::~FunctionDecl() {
	delete functionHead;
	delete subRoutine;
}


FunctionHead::FunctionHead(std::string name, Parameters * parameters, SimpleTypeDecl * simpleTypeDecl) : name(name), parameters(parameters), simpleTypeDecl(simpleTypeDecl) {}

std::vector<ASTNode *> FunctionHead::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(parameters);
	ch.push_back(simpleTypeDecl);
	return ch;
	}

std::string FunctionHead::getName() {
	return std::move(name);
}

FunctionHead::~FunctionHead() {
	delete parameters;
	delete simpleTypeDecl;
}


ProcedureDecl::ProcedureDecl(ProcedureHead * procedureHead, SubRoutine * subRoutine) : procedureHead(procedureHead), subRoutine(subRoutine) {}

std::vector<ASTNode *> ProcedureDecl::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(procedureHead);
	ch.push_back(subRoutine);
	return ch;
}

ProcedureDecl::~ProcedureDecl() {
	delete procedureHead;
	delete subRoutine;
}



ProcedureHead::ProcedureHead(std::string name, Parameters * parameters) : name(std::move(name)), parameters(parameters) {}

std::vector<ASTNode *> ProcedureHead::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(parameters);
	return ch;
}

ProcedureHead::~ProcedureHead() {
	delete parameters;
}


Parameters::Parameters(ParaDeclList * paraDeclList) : paraDeclList(paraDeclList) {}
Parameters::Parameters() {}

std::vector<ASTNode *> Parameters::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(paraDeclList)
		ch.push_back(paraDeclList);
	return ch;
}

Parameters::~Parameters() {
	delete paraDeclList;
}


ParaDeclList::ParaDeclList(ParaDeclList * preList, ParaTypeList * paraTypeList) : preList(preList), paraTypeList(paraTypeList) {}

ParaDeclList::ParaDeclList(ParaTypeList * paraTypeList) : paraTypeList(paraTypeList) {}

std::vector<ASTNode *> ParaDeclList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(paraTypeList);
	return ch;
}



ParaTypeList::ParaTypeList(VarParaList * varParaList, SimpleTypeDecl * simpleTypeDecl) : varParaList(varParaList), simpleTypeDecl(simpleTypeDecl) {}

ParaTypeList::ParaTypeList(ValParaList * valParaList, SimpleTypeDecl * simpleTypeDecl) : valParaList(valParaList), simpleTypeDecl(simpleTypeDecl) {}

std::vector<ASTNode *> ParaTypeList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(varParaList)
		ch.push_back(varParaList);
	if(valParaList)
		ch.push_back(valParaList);
	ch.push_back(simpleTypeDecl);
	return ch;
}

ParaTypeList::~ParaTypeList() {
	delete varParaList;
	delete valParaList;
}

VarParaList::VarParaList(NameList * nameList) : nameList(nameList) {}

std::vector<ASTNode *> VarParaList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(nameList);
	return ch;
}

VarParaList::~VarParaList() {
	delete nameList;
}


ValParaList::ValParaList(NameList * nameList) : nameList(nameList) {}

std::vector<ASTNode *> ValParaList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(nameList);
	return ch;
}

ValParaList::~ValParaList() {
	delete nameList;
}


RoutineBody::RoutineBody(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}

std::vector<ASTNode *> RoutineBody::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(compoundStmt);
	return ch;
}

RoutineBody::~RoutineBody() {
	delete compoundStmt;
}


CompoundStmt::CompoundStmt(StmtList * stmtList) : stmtList(stmtList) {}

std::vector<ASTNode *> CompoundStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(stmtList);
	return ch;
}

CompoundStmt::~CompoundStmt() {
	delete stmtList;
}


StmtList::StmtList(StmtList * preList, Stmt * stmt) : preList(preList), stmt(stmt) {}

StmtList::StmtList() {}

std::vector<ASTNode *> StmtList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(stmt);
	return ch;
}

StmtList::~StmtList() {
	delete preList;
	delete stmt;
}


Stmt::Stmt(std::string label, NonLabelStmt * nonLabelStmt) : label(std::move(label)), nonLabelStmt(nonLabelStmt) {}

Stmt::Stmt(NonLabelStmt * nonLabelStmt) : nonLabelStmt(nonLabelStmt) {}

std::vector<ASTNode *> Stmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(nonLabelStmt);
	return ch;
}

Stmt::~Stmt() {
	delete nonLabelStmt;
}



NonLabelStmt::NonLabelStmt(AssignStmt * assignStmt) : assignStmt(assignStmt) {}

NonLabelStmt::NonLabelStmt(ProcStmt * procStmt) : procStmt(procStmt) {}

NonLabelStmt::NonLabelStmt(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}

NonLabelStmt::NonLabelStmt(IfStmt * ifStmt) : ifStmt(ifStmt) {}

NonLabelStmt::NonLabelStmt(RepeatStmt * repeatStmt) : repeatStmt(repeatStmt) {}

NonLabelStmt::NonLabelStmt(WhileStmt * whileStmt) : whileStmt(whileStmt) {}

NonLabelStmt::NonLabelStmt(ForStmt * forStmt) : forStmt(forStmt) {}

NonLabelStmt::NonLabelStmt(CaseStmt * caseStmt) : caseStmt(caseStmt) {}

NonLabelStmt::NonLabelStmt(GotoStmt * gotoStmt) : gotoStmt(gotoStmt) {}

std::vector<ASTNode *> NonLabelStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
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

NonLabelStmt::~NonLabelStmt() {
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


AssignStmt::AssignStmt(std::string name, Expression * expression) : name(std::move(name)), expression(expression) {}

AssignStmt::AssignStmt(std::string name, Expression * index, Expression * expression) : name(std::move(name)), index(index), expression(expression) {}

AssignStmt::AssignStmt(std::string name, std::string attr, Expression * expression) : name(std::move(name)), attr(std::move(attr)), expression(expression) {}

std::vector<ASTNode *> AssignStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(index)
		ch.push_back(index);
	ch.push_back(expression);
	return ch;
}

AssignStmt::~AssignStmt() {
	delete expression;
	delete index;
}


ProcStmt::ProcStmt(bool isSysProc, std::string val) {
	if(!isSysProc)
		name = std::move(val);
	else
		sysProc = std::move(val);
}

ProcStmt::ProcStmt(std::string name, ArgsList * argsList) : name(std::move(name)), argsList(argsList) {}

ProcStmt::ProcStmt(std::string sysProc, ExpressionList * expressionList) : sysProc(std::move(sysProc)), expressionList(expressionList) {}

ProcStmt::ProcStmt(Factor * factor) : factor(factor) {}

std::vector<ASTNode *> ProcStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(argsList)
		ch.push_back(argsList);
	if(expressionList)
		ch.push_back(expressionList);
	if(factor)
		ch.push_back(factor);
	return ch;
}

ProcStmt::~ProcStmt() {
	delete argsList;
	delete expressionList;
	delete factor;
}

IfStmt::IfStmt(Expression * expression, Stmt * stmt, ElseClause * elseClause) : expression(expression), stmt(stmt), elseClause(elseClause) {}

std::vector<ASTNode *> IfStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(expression);
	ch.push_back(stmt);
	ch.push_back(elseClause);
	return ch;
}

IfStmt::~IfStmt() {
	delete expression;
	delete stmt;
	delete elseClause;
}

ElseClause::ElseClause(Stmt * stmt) : stmt(stmt) {}

ElseClause::ElseClause() {}

std::vector<ASTNode *> ElseClause::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(stmt);
	return ch;
}

ElseClause::~ElseClause() {
	delete stmt;
}


RepeatStmt::RepeatStmt(StmtList * stmtList, Expression * expression) : stmtList(stmtList), expression(expression) {}

std::vector<ASTNode *> RepeatStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(stmtList);
	ch.push_back(expression);
	return ch;
}

RepeatStmt::~RepeatStmt() {
	delete stmtList;
}


WhileStmt::WhileStmt(Expression * expression, Stmt * stmt) : expression(expression), stmt(stmt) {}

std::vector<ASTNode *> WhileStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(expression);
	ch.push_back(stmt);
	return ch;
}

WhileStmt::~WhileStmt() {
	delete expression;
	delete stmt;
}


ForStmt::ForStmt(std::string name, Expression * expr1, Direction * direction, Expression * expr2, Stmt * stmt) : name(std::move(name)), expr1(expr1), direction(direction), expr2(expr2), stmt(stmt) {}

std::vector<ASTNode *> ForStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(expr1);
	ch.push_back(direction);
	ch.push_back(expr2);
	ch.push_back(stmt);
	return ch;
}

ForStmt::~ForStmt() {
	delete expr1;
	delete expr2;
	delete direction;
	delete stmt;
}

Direction::Direction(std::string dir) : dir(std::move(dir)) {}

std::vector<ASTNode *> Direction::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	return ch;
}

CaseStmt::CaseStmt(Expression * expression, CaseExprList * caseExprList) : expression(expression), caseExprList(caseExprList) {}

std::vector<ASTNode *> CaseStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(expression);
	ch.push_back(caseExprList);
	return ch;
}

CaseStmt::~CaseStmt() {
	delete expression;
	delete caseExprList;
}


CaseExprList::CaseExprList(CaseExprList * preList, CaseExpr * caseExpr) : preList(preList), caseExpr(caseExpr) {}

CaseExprList::CaseExprList(CaseExpr * caseExpr) : caseExpr(caseExpr) {}

std::vector<ASTNode *> CaseExprList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(caseExpr);
	return ch;
}

CaseExprList::~CaseExprList() {
	delete preList;
	delete caseExpr;
}


CaseExpr::CaseExpr(ConstValue * constValue, Stmt * stmt) : constValue(constValue), stmt(stmt) {}

CaseExpr::CaseExpr(std::string name, Stmt * stmt) : name(std::move(name)), stmt(stmt) {}

std::vector<ASTNode *> CaseExpr::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(constValue)
		ch.push_back(constValue);
	ch.push_back(stmt);
	return ch;
}

CaseExpr::~CaseExpr() {
	delete constValue;
	delete stmt;
}


GotoStmt::GotoStmt(std::string address) : address(new ConstValue(286, address)) {}

std::vector<ASTNode *> GotoStmt::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(address);
	return ch;
}

GotoStmt::~GotoStmt() {
	delete address;
}



ExpressionList::ExpressionList(ExpressionList * preList, Expression * expression) : preList(preList), expression(expression) {}

ExpressionList::ExpressionList(Expression * expression) : expression(expression) {}

std::vector<ASTNode *> ExpressionList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(preList);
	ch.push_back(expression);
	return ch;
}

ExpressionList::~ExpressionList() {
	delete preList;
	delete expression;
}

Expression::Expression(Expression * expression, std::string binop, Expr * expr) : expression(expression), binop(std::move(binop)), expr(expr) {}

Expression::Expression(Expr * expr) : expr(expr) {}

std::vector<ASTNode *> Expression::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(expression)
		ch.push_back(expression);
	ch.push_back(expr);
	return ch;
}

Expression::~Expression() {
	delete expression;
	delete expr;
}


Expr::Expr(Expr * expr, std::string binop, Term * term) : expr(expr), binop(std::move(binop)), term(term) {}

Expr::Expr(Term * term) : term(term) {}

std::vector<ASTNode *> Expr::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(expr)
		ch.push_back(expr);
	ch.push_back(term);
	return ch;
}

Expr::~Expr() {
	delete expr;
	delete term;
}

Term::Term(Term * term, std::string binop, Factor * factor) : term(term), binop(std::move(binop)), factor(factor) {}

Term::Term(Factor * factor) : factor(factor) {}

std::vector<ASTNode *> Term::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(term)
		ch.push_back(term);
	ch.push_back(factor);
	return ch;
}

Term::~Term() {
	delete term;
	delete factor;
}


Factor::Factor(int token, std::string val) {
	if(token == 258) {
		name = std::move(val);
	}else if(token == 282){
		sysFunc = std::move(val);
	}
}

Factor::Factor(int token, std::string val, ArgsList * argsList) : argsList(argsList) {
	if(token == 258) {
		name = std::move(val);
	}else if(token == 282){
		sysFunc = std::move(val);
	}
}

Factor::Factor(ConstValue * constValue) : constValue(constValue) {}

Factor::Factor(Expression * expression) : expression(expression) {}

Factor::Factor(int token, Factor * factor) : factor(factor) {
	if(token == 269){
		isMinus = 0;
		inv = 1;
	} else if (token == 271) {
		isMinus = 1;
		inv = 1;
	}
}

Factor::Factor(std::string name, Expression * expression) : name(std::move(name)), expression(expression) {}

Factor::Factor(std::string name, std::string attr) : name(std::move(name)), attr(std::move(attr)) {}

std::vector<ASTNode *> Factor::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	ch.push_back(argsList);
	ch.push_back(constValue);
	ch.push_back(expression);
	ch.push_back(factor);
	return ch;
}

Factor::~Factor() {
	delete argsList;
	delete constValue;
	delete expression;
	delete factor;
}


ArgsList::ArgsList(ArgsList * preList, Expression * expression) : preList(preList), expression(expression) {}

ArgsList::ArgsList(Expression * expression) : expression(expression) {}

std::vector<ASTNode *> ArgsList::getChildren() {
	std::vector<ASTNode *> ch = std::vector<ASTNode *>();
	if(preList)
		ch.push_back(preList);
	ch.push_back(expression);
	return ch;
}

ArgsList::~ArgsList() {
	delete preList;
	delete expression;
}
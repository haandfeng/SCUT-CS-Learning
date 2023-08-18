//
//  yufa.hpp
//  mannual
//
//  Created by 谭演锋 on 2023/6/13.
//

#ifndef yufa_hpp
#define yufa_hpp
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
int GrammaticAlanalysis(std::fstream& , std::fstream& );
int isBlock(std::fstream& , int& , double& , std::fstream& );
int isVarList(std::fstream& , int& , double& );
int isForm(std::fstream& , int& , double& );
int isVariableList(std::fstream& , int& , double& );
int isStatementList(std::fstream& , int& , double& , std::fstream& );
int isState(std::fstream& , int& , double& , std::fstream& );
int isStatement(std::fstream& , int& , double& index, std::fstream& );
int isIfState(std::fstream& , int& , double& , std::fstream& );
int isWhileState(std::fstream& , int& , double& , std::fstream& );
int isCompoundState(std::fstream& , int& , double& , std::fstream& );
int isExpression(std::fstream& , int& , double& );
int isItem(std::fstream& , int& , double& );
int isFactor(std::fstream& , int& , double& );
int isRelationalExpression(std::fstream& , int& , double& , std::fstream& );
int isEelationCharacter(std::fstream& , int& , double& ) ;
int isExpression(int flag, std::fstream& , int& , double& );
#endif /* yufa_hpp */

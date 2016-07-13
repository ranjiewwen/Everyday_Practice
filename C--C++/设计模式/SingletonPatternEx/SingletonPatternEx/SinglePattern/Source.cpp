/*
** FileName     : SingletonPatternDemo5
** Author       : Jelly Young
** Date         : 2013/11/21
** Description  : More information, please go to http://www.jellythink.com
*/

#include <iostream>

#include "Constant.h"
#include "SingletonFactory.h"

using namespace std;

int main(int argc, char *argv[])
{
    // 只能创建一个工厂，不允许切换工厂
	SingletonFactory *factoryA = SingletonFactory::GetInstance(kFactory_A);
	factoryA->Operation();
}
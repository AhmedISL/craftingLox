#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include "Adapters/FileManagerAdapter.hpp"
#include "Factories/TokenFactory.hpp"
#include "Scanner/Scanner.hpp"
int main()
{
    std::unique_ptr<std::string> code = FileManagerAdapter::getInstance().parseFiles();
    std::shared_ptr<TokenFactory>  tokenFactory = std::make_shared<TokenFactory>();
    Scanner scanner(std::move(code),tokenFactory);
}



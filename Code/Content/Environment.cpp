#include "Environment.hpp"
using namespace Simcc::Runtime;
StackMemory* Simcc::Environment::stack_block=new StackMemory();
TokenStream * Simcc::Environment::token_stream = new TokenStream();
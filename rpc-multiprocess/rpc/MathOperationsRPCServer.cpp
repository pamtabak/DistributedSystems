#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <stdexcept>
#include <iostream>
#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#ifdef _WIN32
  #define SLEEP(seconds) SleepEx(seconds * 1000);
#else
  #define SLEEP(seconds) sleep(seconds);
#endif


class ExpMethod : public xmlrpc_c::method
{
public:
  ExpMethod()
  {
    this->_signature = "i:ii";
    this->_help = "This method takes a vector and calculates the exp() of its elements";
  }

  void execute(const xmlrpc_c::paramList &paramList, xmlrpc_c::value* const retvalP)
  {
    std::vector<xmlrpc_c::value> v = paramList.getArray(0);
    const int v_sz                 = paramList.getInt(1);

    paramList.verifyEnd(2);
    
    for(size_t i = 0, sz = v.size(); i < sz; i++)
    {
      std::cout << xmlrpc_c::value_double(v[i]) << std::endl;
      //v[i] = xmlrpc_c::value_double(exp(xmlrpc_c::value_double(v[i])));
      std::cout << xmlrpc_c::value_double(v[i]) << std::endl;
    }

    *retvalP = xmlrpc_c::value_array(v);
  }
};


int main(const int argc, const char *argv[])
{
  try {
    xmlrpc_c::registry registry;

    xmlrpc_c::methodPtr const expMethodP(new ExpMethod);

    registry.addMethod("expMethod.rpc", expMethodP);

    xmlrpc_c::serverAbyss server(
	  xmlrpc_c::serverAbyss::constrOpt()
          .registryP(&registry)
	  .portNumber(8080));

    server.run();

    assert(false);
  }
  catch (const std::exception &e) {
    std::cerr << "Something failed. " << e.what() << std::endl;
  }
}

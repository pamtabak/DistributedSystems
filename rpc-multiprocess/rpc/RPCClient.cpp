#include <stdlib.h>
#include <string>
#include <iostream>

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

int main(const int argc, const char *argv[])
{
    if (argc-1 > 0) {
      std::cerr << "This program has no arguments" << std::endl;
      exit(1);
    }

    try {
      std::string const serverUrl("http://localhost:8080/RPC2");
      std::string const methodName("expMethod.rpc");

      xmlrpc_c::clientSimple client;
      xmlrpc_c::value result;

      double v[] = {0.0, 1.0, 2.0, 3.0, 4.0};
      int v_sz = 5;

      xmlrpc_c::value_array v_array(xmlrpc_c::arrayValueArray(v, v_sz));
      
      xmlrpc_c::paramList params;
      params.add(v_array);
      params.addc(v_sz);
        
      client.call(serverUrl, methodName, params, &result);
      
      const std::vector<xmlrpc_c::value> v_result(xmlrpc_c::value_array(result).vectorValueValue());

    } catch (std::exception const& e) {
      std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Client threw unexpected error." << std::endl;
    }

    return 0;
}

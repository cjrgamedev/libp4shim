#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/* p4 2012.1 clients call getaddrinfo with ai_flags in hints that
 * are not supported on Linux 2.4 (specifically AI_ALL and AI_ADDRCONFIG).
 *
 * This shim sets the ai_flags member to AI_PASSIVE which is supported.
 */

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
  static int (*libp4shim)(const char *node, const char *service,
                          const struct addrinfo *hints,
                          struct addrinfo **res);

  struct addrinfo myhints;
  const struct addrinfo *pmyhints = &myhints;
  myhints = *hints;
  myhints.ai_flags = AI_PASSIVE;

  if (!libp4shim)
  {
    void *handle = NULL;
    char *error = NULL;
    handle = dlopen("libc.so.6", RTLD_LAZY);
    if (!handle)
    {
      fputs(dlerror(), stderr);
      exit(EXIT_FAILURE);
    }
    libp4shim = dlsym(handle, "getaddrinfo");
    if ((error = dlerror()) != NULL)
    {
      fprintf(stderr, "libp4shim: %s\n", error);
      exit(EXIT_FAILURE);
    }
    
    fprintf(stderr, "libp4shim: initialised.\n");
  }

  return libp4shim(node, service, pmyhints, res);
}
  

//qua 26 jul 2023 10:08:42 
//w2l -c -g -U -F -P -u  /home/fabiolinux/Documentos/GITHUB/PREPARO/cwitsml/api/PARSERS/witsml_v1.4.1.1_data/generated_update_schemas/* -o update1411.h -tupdate1411.dat
//scpp -c -S -s -t -2 -pupdate1411 update1411.h

//gcc -O2 -c read1411C.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NOGLOBAL -o read1411C.o

//TRY
//OK -> gcc -O2 -c read1411C.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -o read1411C.o
//OK -> int rd1411__readattachments(struct rd1witsml__obj_USCOREattachments *attachments, char **result);
// -DWITH_NOSERVEREQUEST
//OK -> gcc -O2 -c read1411ServerLib.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -o read1411ServerLib.o

//gcc -O2 -c read1411ServerLib.c -I../../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST -o read1411ServerLibDEBUG.o

//NO DEBUG:
//gcc -O2 -c read1411ServerLib.c -I../../../include -Wall -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST -o read1411ServerLib.o

#include "update/update1411H.h"

SOAP_FMAC5 int SOAP_FMAC6 up1411__updateObj1411(struct soap *soap_internal, struct up1411__updateObj1411_USCOREt *obj, char **result)
{
  *result="Soap internal (UPDATE) OK";
  printf("\nSoap internal (UPDATE) %p with obj %p and attachments %p\n", soap_internal, obj, obj->attachments);
  return SOAP_OK;
}


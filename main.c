//10/fev/2024
#include <cws_soap.h>
#include <cws_utils.h>

CWS_BUILDER_14X_13X

int main(int argc, char **argv)
{
  int err;
  const char *text;
  size_t text_len;
  CWS_CONFIG *config;

  if (argc!=2) {
    printf("\nCheck %s <FILE_NAME>\n", *argv);
    return -1;
  }

  if ((err=readText(&text, &text_len, argv[1]))) {
    printf("\nreadText error %d\n", err);
    return err;
  }

  config=cws_config_new(NULL, NULL, 0, ACTION_READ_141X);

  if (!config) {
    fprintf(stderr, "Error at init config\n");
    goto exit_1;
  }

  if (!cws_parse_XML_soap_envelope(config, (char *)text, text_len))
    goto exit_2;

  if ((err=cws_internal_serve(config)))
    printf("\ncws_internal_serve error %d\n", err);

exit_2:
  printf("\nRESUME:\n");
  printf("\ninternal_soap_error -> %d\n", config->internal_soap_error);
  printf("\nconfig->cws_soap_fault.XMLDetails -> %s\n", config->cws_soap_fault.XMLfaultdetail);
  printf("\nconfig->base_msg.code -> %d\n", config->base_msg.code);
  printf("\nconfig->base_msg.message -> %s\n", config->base_msg.message);

  cws_config_free(&config);

exit_1:
  readTextFree(&text);

  return err;
}


float validarFloatRango(float a, float b);
void leercadena(char *cadena, int n);
int contieneTexto(char *texto, char *buscado);
int buscarIndiceStock(char *buscado, char nombresStock[][30], char nombresUso[][30], int totalStock);
void gestionarReceta(int pos, float recetas[][27], char nombres[][50], char nombresStock[][30],
                     char nombresUso[][30], char unidadStock[][15], int totalStock);
void ingresarLimitesJornada(float *tiempoDisp);
void ingresarStock(char nombresStock[][30], int *cantUnidades, float *cantGramos, 
                   char unidadStock[][15], int totalStock);
int mostrarProductos(int *id, char nombres[][50], int *demanda, 
                     float *tiempo, int *estado, int n, int contP);
void ingresarDemanda(int *id, char nombres[][50], int *demanda, 
                     float *tiempo, int *estado, int contP);
int buscarProducto(int *id, char nombres[][50], int *demanda, 
                   float *tiempo, int *estado, int contP);
void editarProducto(int *id, char nombres[][50], int *demanda, 
                    float *tiempo, int *estado, float recetas[][27], int *contP,
                    char nombresStock[][30], char nombresUso[][30], 
                    char unidadStock[][15], int totalStock);
void eliminarProducto(int *id, char nombres[][50], int *demanda, 
                      float *tiempo, int *estado, int contP);
void calcularProduccion(int *id, char nombres[][50], int *demanda, 
                        float *tiempo, int *estado, float recetas[][27], int contP, 
                        float tiempoDisp, char nombresStock[][30], 
                        char nombresUso[][30], char unidadStock[][15], int *cantUnidades, 
                        float *cantGramos, int *factorConversion, int totalStock);

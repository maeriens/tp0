#include "client.h"
#include <readline/readline.h>

int main(void) {
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola, soy un log!");

	config = iniciar_config();

	if (config_has_property(config, "IP")) {
		ip = config_get_string_value(config, "IP");
	} else {
		log_info(logger, "No hay ip!");
	}

	if (config_has_property(config, "PUERTO")) {
		puerto = config_get_string_value(config, "PUERTO");
	} else {
		log_info(logger, "No hay Puerto!");
	}

	if (config_has_property(config, "CLAVE")) {
		clave = config_get_string_value(config, "CLAVE");
	} else {
		log_info(logger, "No hay CLAVE!");
	}

//	leer_consola(logger);

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	//Loggear valor de config

	log_info(logger, "IP %s Puerto %s Clave %s", ip, puerto, clave);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.
	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	log_info(logger, "Enviando clave a conexión %d", conexion);
	// enviar CLAVE al servidor
	enviar_mensaje(clave, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void) {
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log", "TP0", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void) {
	t_config* nuevo_config;
	nuevo_config = config_create("./tp0.config");
	if (nuevo_config == NULL) {
		printf("No hay config!");
		exit(1);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger) {
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline("> ");

	while (strcmp(leido, "") != 0) {
		log_info(logger, leido);
		free(leido);
		leido = readline("> ");
	}

	free(leido);
}

void paquete(int conexion) {
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;

	leido = "Prueba";

	paquete = crear_paquete();
	agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config) {
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	if (logger != NULL) {
		log_destroy(logger);
	}
	if (config != NULL) {
		config_destroy(config);
	}
	if (conexion != NULL) {
		liberar_conexion(conexion);
	}
}

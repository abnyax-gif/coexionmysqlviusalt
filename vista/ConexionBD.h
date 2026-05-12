#pragma once

#include <mysql.h>
#include <iostream>

using namespace std;

class ConexionBD {

private:

	MYSQL* conector;

public:

	ConexionBD() {
		conector = NULL;
	}

	void abrir_conexion() {

		conector = mysql_init(0);

		conector = mysql_real_connect(
			conector,
			"localhost",
			"root",
			"36938772",
			"db_escuela",
			3306,
			NULL,
			0
		);

		if (conector) {
			cout << "Conexion Exitosa..." << endl;
		}
		else {
			cout << "Error en conexion..." << endl;
		}
	}

	MYSQL* getConector() {

		return conector;
	}

	void cerrar_conexion() {

		if (conector != NULL) {
			mysql_close(conector);
		}
	}
};
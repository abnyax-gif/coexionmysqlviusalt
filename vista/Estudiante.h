#pragma once

#define _HAS_STD_BYTE 0

#include "Persona.h"
#include "ConexionBD.h"

#include <iostream>
#include <mysql.h>
#include <string>
#include <regex>
#include <ctime>

using namespace std;

class Estudiante : public Persona {

private:

	string codigo;
	int id_estudiante = 0;

public:

	// ================= CONSTRUCTORES =================

	Estudiante() {}

	Estudiante(
		string nom,
		string ape,
		string dir,
		string tel,
		string fn,
		int id_ts,
		string cod,
		int id_e
	) : Persona(nom, ape, dir, tel, fn, id_ts) {

		codigo = cod;
		id_estudiante = id_e;
	}

	// ================= SET =================

	void setId_estudiante(int e) { id_estudiante = e; }

	void setCodigo(string c) { codigo = c; }

	void setNombres(string n) { nombres = n; }

	void setApellidos(string a) { apellidos = a; }

	void setDireccion(string d) { direccion = d; }

	void setTelefono(string t) { telefono = t; }

	void setFecha_Nacimiento(string f) {
		fecha_nacimiento = f;
	}

	void setId_Tipo_Sangre(int ts) {
		id_tipo_sangre = ts;
	}

	// ================= VALIDAR CODIGO =================

	bool validarCodigo() {

		regex formato("^E[0-9]{3}$");

		return regex_match(codigo, formato);
	}

	// ================= VALIDAR TEXTO =================

	bool validarTexto(string texto) {

		regex formato(
			"^[A-Za-záéíóúÁÉÍÓÚñÑ ]+$"
		);

		return regex_match(texto, formato);
	}

	// ================= VALIDAR TELEFONO =================

	bool validarTelefono() {

		regex formato("^[0-9]{8}$");

		return regex_match(telefono, formato);
	}

	// ================= VALIDAR DIRECCION =================

	bool validarDireccion() {

		if (direccion.empty())
			return false;

		if (
			direccion.find("'") != string::npos ||
			direccion.find(";") != string::npos ||
			direccion.find("--") != string::npos
			) {

			return false;
		}

		return true;
	}

	// ================= VALIDAR FECHA =================

	bool validarFecha() {

		regex formato("^\\d{4}-\\d{2}-\\d{2}$");

		if (!regex_match(fecha_nacimiento, formato)) {

			return false;
		}

		int anio =
			stoi(fecha_nacimiento.substr(0, 4));

		int mes =
			stoi(fecha_nacimiento.substr(5, 2));

		int dia =
			stoi(fecha_nacimiento.substr(8, 2));

		time_t t = time(0);

		tm hoy;

		localtime_s(&hoy, &t);

		int anioActual = hoy.tm_year + 1900;

		if (anio > anioActual)
			return false;

		int diasMes[] = {
			31,28,31,30,31,30,
			31,31,30,31,30,31
		};

		if (mes < 1 || mes > 12)
			return false;

		if (dia < 1 || dia > diasMes[mes - 1])
			return false;

		return true;
	}

	// ================= EXISTE CODIGO =================

	bool existeCodigo() {

		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConector()) {

			string consulta =
				"SELECT * FROM estudiantes "
				"WHERE codigo = '" + codigo + "'";

			const char* c = consulta.c_str();

			int q_estado =
				mysql_query(cn.getConector(), c);

			if (!q_estado) {

				MYSQL_RES* resultado =
					mysql_store_result(
						cn.getConector()
					);

				if (resultado != NULL) {

					if (mysql_num_rows(resultado) > 0) {

						mysql_free_result(resultado);

						cn.cerrar_conexion();

						return true;
					}

					mysql_free_result(resultado);
				}
			}
		}

		cn.cerrar_conexion();

		return false;
	}

	// ================= EXISTE TIPO SANGRE =================

	bool existeTipoSangre() {

		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConector()) {

			string consulta =
				"SELECT * FROM tipos_sangre "
				"WHERE id_tipo_sangre = "
				+ to_string(id_tipo_sangre);

			const char* c = consulta.c_str();

			int q_estado =
				mysql_query(cn.getConector(), c);

			if (!q_estado) {

				MYSQL_RES* resultado =
					mysql_store_result(
						cn.getConector()
					);

				if (resultado != NULL) {

					if (mysql_num_rows(resultado) > 0) {

						mysql_free_result(resultado);

						cn.cerrar_conexion();

						return true;
					}

					mysql_free_result(resultado);
				}
			}
			else {

				cout << "ERROR MYSQL: "
					<< mysql_error(
						cn.getConector()
					)
					<< endl;
			}
		}

		cn.cerrar_conexion();

		return false;
	}

	// ================= CREAR =================

	void crear() {

		int q_estado = 0;

		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConector()) {

			string id_ts =
				to_string(id_tipo_sangre);

			string consulta =
				"INSERT INTO estudiantes("
				"codigo,"
				"nombres,"
				"apellidos,"
				"direccion,"
				"telefono,"
				"fecha_nacimiento,"
				"id_tipo_sangre"
				") VALUES('"
				+ codigo + "','"
				+ nombres + "','"
				+ apellidos + "','"
				+ direccion + "','"
				+ telefono + "','"
				+ fecha_nacimiento + "',"
				+ id_ts + ");";

			const char* c = consulta.c_str();

			q_estado =
				mysql_query(
					cn.getConector(),
					c
				);

			if (!q_estado) {

				cout << "\nIngreso Exitoso...\n";
			}
			else {

				cout << "\nConsulta Fallida...\n";

				cout << "ERROR MYSQL: "
					<< mysql_error(
						cn.getConector()
					)
					<< endl;
			}
		}

		cn.cerrar_conexion();
	}

	// ================= LEER =================

	void leer() {

		int q_estado = 0;

		ConexionBD cn = ConexionBD();

		MYSQL_ROW fila;

		MYSQL_RES* resultado;

		cn.abrir_conexion();

		if (cn.getConector()) {

			cout << "\n__ ESTUDIANTES __\n\n";

			string consulta =
				"SELECT "
				"e.id_estudiante,"
				"e.codigo,"
				"e.nombres,"
				"e.apellidos,"
				"e.direccion,"
				"e.telefono,"
				"e.fecha_nacimiento,"
				"ts.sangre "
				"FROM estudiantes e "
				"INNER JOIN tipos_sangre ts "
				"ON e.id_tipo_sangre = "
				"ts.id_tipo_sangre;";

			const char* c = consulta.c_str();

			q_estado =
				mysql_query(
					cn.getConector(),
					c
				);

			if (!q_estado) {

				resultado =
					mysql_store_result(
						cn.getConector()
					);

				while (
					(fila = mysql_fetch_row(resultado))
					) {

					cout
						<< fila[0] << " | "
						<< fila[1] << " | "
						<< fila[2] << " | "
						<< fila[3] << " | "
						<< fila[4] << " | "
						<< fila[5] << " | "
						<< fila[6] << " | "
						<< fila[7]
						<< endl;
				}
			}
		}

		cn.cerrar_conexion();
	}
};
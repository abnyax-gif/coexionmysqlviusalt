#pragma once
#include <iostream>

using namespace std;

class Persona {

protected:

	string nombres, apellidos, direccion, fecha_nacimiento;
	string telefono;
	int id_tipo_sangre = 0;

public:

	Persona() {}

	Persona(
		string nom,
		string ape,
		string dir,
		string tel,
		string fn,
		int id_ts
	) {

		nombres = nom;
		apellidos = ape;
		direccion = dir;
		telefono = tel;
		fecha_nacimiento = fn;
		id_tipo_sangre = id_ts;
	}
};
#define _HAS_STD_BYTE 0

#include <iostream>
#include <Windows.h>
#include "Estudiante.h"

using namespace std;

int main() {

	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	string telefono;

	int id_tipo_sangre = 0;
	int id_estudiante = 0;

	Estudiante e;

	// ================= CODIGO =================

	do {

		cout << "Ingrese Codigo (E001): ";
		cin >> codigo;

		e.setCodigo(codigo);

		if (!e.validarCodigo()) {

			cout << "ERROR: Codigo invalido. Ejemplo correcto: E001\n\n";
		}
		else if (e.existeCodigo()) {

			cout << "ERROR: El codigo ya existe.\n\n";
		}

	} while (!e.validarCodigo() || e.existeCodigo());

	cin.ignore();

	// ================= NOMBRES =================

	do {

		cout << "Ingrese Nombres: ";
		getline(cin, nombres);

		e.setNombres(nombres);

		if (!e.validarTexto(nombres)) {

			cout << "ERROR: Nombres invalidos.\n\n";
		}

	} while (!e.validarTexto(nombres));

	// ================= APELLIDOS =================

	do {

		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);

		e.setApellidos(apellidos);

		if (!e.validarTexto(apellidos)) {

			cout << "ERROR: Apellidos invalidos.\n\n";
		}

	} while (!e.validarTexto(apellidos));

	// ================= DIRECCION =================

	do {

		cout << "Ingrese Direccion: ";
		getline(cin, direccion);

		e.setDireccion(direccion);

		if (!e.validarDireccion()) {

			cout << "ERROR: Direccion invalida.\n\n";
		}

	} while (!e.validarDireccion());

	// ================= TELEFONO =================

	do {

		cout << "Ingrese Telefono (8 digitos): ";
		cin >> telefono;

		e.setTelefono(telefono);

		if (!e.validarTelefono()) {

			cout << "ERROR: Telefono invalido.\n\n";
		}

	} while (!e.validarTelefono());

	cin.ignore();

	// ================= FECHA =================

	do {

		cout << "Ingrese Fecha Nacimiento (AAAA-MM-DD): ";
		getline(cin, fecha_nacimiento);

		e.setFecha_Nacimiento(fecha_nacimiento);

		if (!e.validarFecha()) {

			cout << "ERROR: Fecha invalida.\n\n";
		}

	} while (!e.validarFecha());

	// ================= TIPO SANGRE =================

	do {

		cout << "Ingrese Tipo Sangre: ";
		cin >> id_tipo_sangre;

		e.setId_Tipo_Sangre(id_tipo_sangre);

		if (!e.existeTipoSangre()) {

			cout << "ERROR: Tipo de sangre no existe.\n\n";
		}

	} while (!e.existeTipoSangre());

	// ================= CREAR OBJETO =================

	Estudiante estudiante(
		nombres,
		apellidos,
		direccion,
		telefono,
		fecha_nacimiento,
		id_tipo_sangre,
		codigo,
		id_estudiante
	);

	// ================= GUARDAR =================

	estudiante.crear();

	// ================= MOSTRAR =================

	estudiante.leer();

	system("pause");

	return 0;
}
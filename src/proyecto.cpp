#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Definición de constantes para tamaños máximos
const int MAX_USUARIOS = 100;
const int MAX_LIBROS = 100;

// Definición de la estructura para usuarios
struct Usuario {
    string nombre;
    string apellido;
    string id;
    string usuario;
    string clave;
    string estado;
    string rol;
};

// Definición de la estructura para libros
struct Libro {
    string titulo;
    string autor;
    int anio;
    string genero;
    float precio_renta;
    float precio_compra;
    int codigo;
    string estado;
};

// Función para cargar usuarios desde archivo CSV
int cargarUsuarios(Usuario usuarios[], int& numUsuarios) {
    ifstream archivo("./data/usuarios.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return -1;
    }

    string linea;
    getline(archivo, linea); // Leer encabezado

    numUsuarios = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, usuarios[numUsuarios].nombre, ',');
        getline(ss, usuarios[numUsuarios].apellido, ',');
        getline(ss, usuarios[numUsuarios].id, ',');
        getline(ss, usuarios[numUsuarios].usuario, ',');
        getline(ss, usuarios[numUsuarios].clave, ',');
        getline(ss, usuarios[numUsuarios].estado, ',');
        getline(ss, usuarios[numUsuarios].rol, ',');
        numUsuarios++;
    }

    archivo.close();
    return 0;
}

// Función para cargar libros desde archivo CSV
int cargarLibros(Libro libros[], int& numLibros) {
    ifstream archivo("./data/libros.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo de libros." << endl;
        return -1;
    }

    string linea;
    getline(archivo, linea); // Leer encabezado

    numLibros = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, libros[numLibros].titulo, ',');
        getline(ss, libros[numLibros].autor, ',');
        ss >> libros[numLibros].anio;
        ss.ignore();
        getline(ss, libros[numLibros].genero, ',');
        ss >> libros[numLibros].precio_renta;
        ss.ignore();
        ss >> libros[numLibros].precio_compra;
        ss.ignore();
        ss >> libros[numLibros].codigo;
        ss.ignore();
        getline(ss, libros[numLibros].estado, ',');
        numLibros++;
    }

    archivo.close();
    return 0;
}

// Función para guardar usuarios en archivo CSV
int guardarUsuarios(const Usuario usuarios[], int numUsuarios) {
    ofstream archivo("./data/usuarios.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo de usuarios para guardar." << endl;
        return -1;
    }

    archivo << "nombre,apellido,id,usuario,clave,estado,rol" << endl;
    for (int i = 0; i < numUsuarios; ++i) {
        archivo << usuarios[i].nombre << ',' << usuarios[i].apellido << ',' << usuarios[i].id << ','
                << usuarios[i].usuario << ',' << usuarios[i].clave << ',' << usuarios[i].estado << ',' << usuarios[i].rol << endl;
    }

    archivo.close();
    return 0;
}

// Función para guardar libros en archivo CSV
int guardarLibros(const Libro libros[], int numLibros) {
    ofstream archivo("./data/libros.csv");
    if (!archivo) {
        cout << "Error al abrir el archivo de libros para guardar." << endl;
        return -1;
    }

    archivo << "titulo,autor,anio,genero,precio_renta,precio_compra,codigo,estado" << endl;
    for (int i = 0; i < numLibros; ++i) {
        archivo << libros[i].titulo << ',' << libros[i].autor << ',' << libros[i].anio << ','
                << libros[i].genero << ',' << libros[i].precio_renta << ',' << libros[i].precio_compra << ','
                << libros[i].codigo << ',' << libros[i].estado << endl;
    }

    archivo.close();
    return 0;
}

// Función para autenticar usuario
bool iniciarSesion(string& usuario, string& clave, Usuario usuarios[], int numUsuarios, int& indiceUsuario) {
    cout << "Inicio de sesión" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Clave: ";
    cin >> clave;

    for (int i = 0; i < numUsuarios; ++i) {
        if (usuarios[i].usuario == usuario && usuarios[i].clave == clave) {
            indiceUsuario = i;
            cout << "Bienvenido, " << usuarios[indiceUsuario].nombre << "!" << endl;
            return true;
        }
    }

    cout << "Error: Usuario o contraseña incorrectos." << endl;
    return false;
}

// Función para agregar un nuevo usuario
void agregarUsuario(Usuario usuarios[], int& numUsuarios) {
    Usuario nuevoUsuario;
    cout << "Ingrese nombre: ";
    cin >> nuevoUsuario.nombre;
    cout << "Ingrese apellido: ";
    cin >> nuevoUsuario.apellido;
    cout << "Ingrese ID: ";
    cin >> nuevoUsuario.id;
    cout << "Ingrese usuario: ";
    cin >> nuevoUsuario.usuario;
    cout << "Ingrese clave: ";
    cin >> nuevoUsuario.clave;
    nuevoUsuario.estado = "activo";
    cout << "Ingrese rol (admin/empleado/cliente): ";
    cin >> nuevoUsuario.rol;

    usuarios[numUsuarios] = nuevoUsuario;
    numUsuarios++;

    guardarUsuarios(usuarios, numUsuarios);
}

// Función para eliminar un usuario
void eliminarUsuario(Usuario usuarios[], int& numUsuarios) {
    string usuarioEliminar;
    cout << "Ingrese el usuario a eliminar: ";
    cin >> usuarioEliminar;

    for (int i = 0; i < numUsuarios; ++i) {
        if (usuarios[i].usuario == usuarioEliminar) {
            usuarios[i].estado = "eliminado";
            break;
        }
    }

    guardarUsuarios(usuarios, numUsuarios);
}

// Función para agregar un nuevo libro
void agregarLibro(Libro libros[], int& numLibros) {
    Libro nuevoLibro;
    cout << "Ingrese título: ";
    cin.ignore();
    getline(cin, nuevoLibro.titulo);
    cout << "Ingrese autor: ";
    getline(cin, nuevoLibro.autor);
    cout << "Ingrese año: ";
    cin >> nuevoLibro.anio;
    cout << "Ingrese género: ";
    cin.ignore();
    getline(cin, nuevoLibro.genero);
    cout << "Ingrese precio de renta: ";
    cin >> nuevoLibro.precio_renta;
    cout << "Ingrese precio de compra: ";
    cin >> nuevoLibro.precio_compra;
    cout << "Ingrese código: ";
    cin >> nuevoLibro.codigo;
    cout << "Ingrese estado (disponible/no disponible): ";
    cin.ignore();
    getline(cin, nuevoLibro.estado);

    libros[numLibros] = nuevoLibro;
    numLibros++;

    guardarLibros(libros, numLibros);
}

// Función para eliminar un libro
void eliminarLibro(Libro libros[], int& numLibros) {
    int codigoEliminar;
    cout << "Ingrese el código del libro a eliminar: ";
    cin >> codigoEliminar;

    for (int i = 0; i < numLibros; ++i) {
        if (libros[i].codigo == codigoEliminar) {
            libros[i].estado = "eliminado";
            break;
        }
    }

    guardarLibros(libros, numLibros);
}

// Función principal que maneja el flujo del programa
int main() {
    Usuario usuarios[MAX_USUARIOS];
    Libro libros[MAX_LIBROS];
    int numUsuarios = 0;
    int numLibros = 0;

    if (cargarUsuarios(usuarios, numUsuarios) != 0 || cargarLibros(libros, numLibros) != 0) {
        return 1;
    }

    string usuario, clave;
    int indiceUsuario = -1;

    if (!iniciarSesion(usuario, clave, usuarios, numUsuarios, indiceUsuario)) {
        return 1;
    }

    if (usuarios[indiceUsuario].rol == "admin") {
        int opcion;
        do {
            cout << "\n--- Menú de Administrador ---\n";
            cout << "1. Agregar usuario\n";
            cout << "2. Eliminar usuario\n";
            cout << "3. Agregar libro\n";
            cout << "4. Eliminar libro\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarUsuario(usuarios, numUsuarios);
                    break;
                case 2:
                    eliminarUsuario(usuarios, numUsuarios);
                    break;
                case 3:
                    agregarLibro(libros, numLibros);
                    break;
                case 4:
                    eliminarLibro(libros, numLibros);
                    break;
                case 5:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    break;
            }
        } while (opcion != 5);
    } else if (usuarios[indiceUsuario].rol == "empleado") {
        int opcion;
        do {
            cout << "\n--- Menú de Empleado ---\n";
            cout << "1. Agregar libro\n";
            cout << "2. Eliminar libro\n";
            cout << "3. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarLibro(libros, numLibros);
                    break;
                case 2:
                    eliminarLibro(libros, numLibros);
                    break;
                case 3:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    break;
            }
        } while (opcion != 3);
    } else if (usuarios[indiceUsuario].rol == "cliente") {
        int opcion;
        do {
            cout << "\n--- Menú de Cliente ---\n";
            cout << "1. Ver libros disponibles\n";
            cout << "2. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    for (int i = 0; i < numLibros; ++i) {
                        if (libros[i].estado == "disponible") {
                            cout << "Título: " << libros[i].titulo << endl;
                            cout << "Autor: " << libros[i].autor << endl;
                            cout << "Año: " << libros[i].anio << endl;
                            cout << "Género: " << libros[i].genero << endl;
                            cout << "Precio de renta: " << libros[i].precio_renta << endl;
                            cout << "----------------------" << endl;
                        }
                    }
                    break;
                case 2:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    break;
            }
        } while (opcion != 2);
    }

    return 0;
}

#include <iostream>  
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

const int Maxi-Atletas = 100;
std::string nombres[Maxi_Atletas];
std::string paises[Maxi_Atletas];
std::string disciplinas[Maxi_Atletas];
char generos[Maxi_Atletas];
int medallas[Maxi_Atletas];
int n_atletas = 0;

bool cargarDatos(const std::string& ruta);
int buscarAtleta(const std::string& nombre);
int totalMedallasPorPais(const std::string& pais);
int atletaConMasMedallas();
void mostrarAtleta(int indice);
void limpiarEntrada();

int main(int argc, char* argv[]) {
    std::string rutaArchivo;

    if (argc > 1)
        rutaArchivo = argv[1];
    else
        std::getline(std::cin, rutaArchivo);

    if (!cargarDatos(rutaArchivo))
        return 1;

    while (true) {
        int opcion;
        std::cin >> opcion;
        if (std::cin.fail()) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();

        if (opcion == 1) {
            std::string nombreBuscar;
            std::getline(std::cin, nombreBuscar);
            int idx = buscarAtleta(nombreBuscar);
            if (idx == -1) {
                // atleta no encontrado
            } else {
                mostrarAtleta(idx);
            }
        } else if (opcion == 2) {
            std::string paisBuscar;
            std::getline(std::cin, paisBuscar);
            int total = totalMedallasPorPais(paisBuscar);
            // total medallas para los paises 
        } else if (opcion == 3) {
            int idxMax = atletaConMasMedallas();
            if (idxMax != -1) {
                mostrarAtleta(idxMax);
            }
        } else if (opcion == 4) {
            break;
        }
    }
    return 0;
}

bool cargarDatos(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open())
        return false;
    std::string linea;
    std::getline(archivo, linea);
    n_atletas = 0;
    while (std::getline(archivo, linea) && n_atletas < MAX_ATLETAS) {
        std::stringstream ss(linea);
        std::string medallasStr, generoStr;
        if (!std::getline(ss, nombres[n_atletas], ',')) break;
        if (!std::getline(ss, paises[n_atletas], ',')) break;
        if (!std::getline(ss, disciplinas[n_atletas], ',')) break;
        if (!std::getline(ss, generoStr, ',')) break;
        if (!std::getline(ss, medallasStr)) break;

        generos[n_atletas] = generoStr.empty() ? 'U' : generoStr[0];
        try {
            medallas[n_atletas] = std::stoi(medallasStr);
        } catch (...) {
            medallas[n_atletas] = 0;
        }
        n_atletas++;
    }
    archivo.close();
    return true;
}

int buscarAtleta(const std::string& nombre) {
    for (int i = 0; i < n_atletas; i++)
        if (nombres[i] == nombre)
            return i;
    return -1;
}

int totalMedallasPorPais(const std::string& pais) {
    int total = 0;
    for (int i = 0; i < n_atletas; i++)
        if (paises[i] == pais)
            total += medallas[i];
    return total;
}

int atletaConMasMedallas() {
    if (n_atletas == 0) return -1;
    int idxMax = 0;
    for (int i = 1; i < n_atletas; i++)
        if (medallas[i] > medallas[idxMax])
            idxMax = i;
    return idxMax;
}

void mostrarAtleta(int indice) {
    std::cout << nombres[indice] << "\n"
              << paises[indice] << "\n"
              << disciplinas[indice] << "\n"
              << generos[indice] << "\n"
              << medallas[indice] << "\n";
}

void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//No se como lo hice pero sin esto no compila en mi pc lo intente e igual que los repositorios dios me vendigan a todos
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iomanip>

enum TipoComando {
    EV, // EVENTO
    PC, // CONSULTA PACOTE
    CL  // CONSULTA CLIENTE
};

enum TipoEvento {
    RG, // Pacote ainda não foi postado (apenas registrado no sistema)
    AR, // Pacote chegou no armazém e foi armazenado na respectiva seção
    RM, // Pacote foi removido da seção para tentativa de transporte
    UR, // Pacote foi rearmazenado por não ser possível transportá-lo
    TR, // Pacote sendo transportado entre armazéns
    EN  // Pacote entregue
};

// ATRIBUTOS DE CADA EVENTO:
// RG: data_hora EV tipo_evento id_pacote remetente destinatario armazem_origem armazem_destino
// AR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// RM: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// UR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// TR: data_hora EV tipo_evento id_pacote armazem_origem armazem_destino
// EN: data_hora EV tipo_evento id_pacote armazem_destino

class Utils {
    public:

        // EVENTOS
        static TipoEvento stringToTipoEvento(const std::string& str);
        static std::string tipoEventoToString(TipoEvento tipo);
        static std::string intToString(int num, int width = 3);

        // COMANDOS
        static TipoComando stringToTipoComando(const std::string& comando);

        // OUTRAS FUNÇÕES
        static int getMax(int a, int b);
};

#endif
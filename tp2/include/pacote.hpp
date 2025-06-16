#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <iostream>

class Pacote {
    friend class Evento; // Permite que a classe Evento acesse os membros privados de Pacote

    public:
        enum Estado_Pacote { 
            Nao_Postado,         // 1. Não foi postado
            Chegada_Escalonada,  // 2. Chegada escalonada a um armazém (postagem ou transporte)
            Armazenado,          // 3. Armazenado na seção associada ao próximo destino de um armazém
            Removido,            // 4. Removido da seção para transporte
            Entregue             // 5. Entregue
        };          
            
        Pacote(double tempo_chegada, int id_pacote, int armazem_inicial, int armazem_final);
        ~Pacote();
        
        // MÉTODOS GET
        double GetTempoChegada();
        int GetIdPacote();
        int GetArmazemInicial();
        int GetArmazemFinal();
        Estado_Pacote GetEstado();
        // Lista* GetRota(); 
        double GetTempoArmazenado();
        double GetTempoTransito();

        // MÉTODOS SET
        void SetEstado(Estado_Pacote novo_estado);
        void SetTempoArmazenado(double tempo);
        void SetTempoTransito(double tempo);

        // OUTROS MÉTODOS
        void PrintInfo();
        void PrintRota();
        
    private:
        double tempo_chegada; // Tempo de chegada do pacote
        int id_pacote;        // Identificador do pacote
        int armazem_inicial;  // Armazém inicial do pacote
        int armazem_final;    // Armazém final do pacote

        Estado_Pacote estado;
        //Lista* rota; 

        double tempo_armazenado;
        double tempo_transito;   // Tempo sendo transportado
};

#endif
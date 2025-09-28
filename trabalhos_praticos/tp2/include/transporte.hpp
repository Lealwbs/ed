#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

class Transporte {
    public:
        Transporte(double tempo_entre_viagens, int max_pacotes_por_viagem, int armazem_origem, int armazem_destino ){
            this->tempo_entre_viagens = tempo_entre_viagens;
            this->max_pacotes_por_viagem = max_pacotes_por_viagem;
            this->armazem_origem = armazem_origem;
            this->armazem_destino = armazem_destino; };

    // MÉTODOS GET
    double GetTempoEntreViagens() const { return tempo_entre_viagens; };
    int GetMaxPacotesPorViagem() const { return max_pacotes_por_viagem; };
    int GetArmazemOrigem() const { return armazem_origem; };
    int GetArmazemDestino() const { return armazem_destino; };

    // MÉTODOS SET
    void SetTempoEntreViagens(double tempo) { tempo_entre_viagens = tempo; };
    void SetMaxPacotesPorViagem(int max_pacotes) { max_pacotes_por_viagem = max_pacotes; };
    void SetArmazemOrigem(int armazem) { armazem_origem = armazem; };
    void SetArmazemDestino(int armazem) { armazem_destino = armazem; };

    private:
        double tempo_entre_viagens; 
        int max_pacotes_por_viagem; 
        int armazem_origem;
        int armazem_destino;
};

#endif
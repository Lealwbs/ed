// #include "../include/SistemaLogistico.hpp"

// // Funções auxiliares para extração de chaves das estruturas AVL
// int obterChavePacote(Pacote* p) {
//     return p->getId();
// };

// std::string obterChaveCliente(Cliente* c) {
//     return c->getNome();
// };

// int obterChaveEvento(Evento* e) {
//     // Cria uma chave única baseada em timestamp, ID do pacote e tipo do evento
//     std::stringstream ss;
//     ss << e->getDataHora() 
//        << std::setw(3) << std::setfill('0') << e->getIdPacote() 
//        << static_cast<int>(e->getTipoEvento());
    
//     std::string keyStr = ss.str();
//     return std::stoi(keyStr);
// };

// SistemaLogistico::SistemaLogistico():
//     pacotes(obterChavePacote),
//     clientes(obterChaveCliente),
//     eventos(obterChaveEvento) {};

// SistemaLogistico::~SistemaLogistico(){};

// void SistemaLogistico::processarEvento(const Evento evento) {
//     // 1. Armazenamento do Evento (lógica inalterada)
//     Evento* novoEvento = new Evento(evento);
//     this->eventos.inserir(novoEvento);

//     // 2. Obtenção do Pacote usando o getter getIdPacote()
//     Pacote* pacote = obterOuCriarPacote(novoEvento->getIdPacote());

//     // 3. Vínculo Evento-Pacote
//     // RECOMENDAÇÃO: Armazenar o ponteiro do evento no pacote é mais flexível.
//     // SUPOSIÇÃO: A classe Pacote tem um `std::vector<Evento*> historicoEventos;`
//     pacote->historicoEventos.push_back(novoEvento);

//     // 4. Processamento baseado no TipoEvento (usando o getter)
//     TipoEvento tipo = novoEvento->getTipoEvento();

//     if (tipo == TipoEvento::RG) {
//         // Para o evento de Registro Global, vinculamos os clientes
        
//         // Obter nomes usando os getters getRemetente() e getDestinatario()
//         Cliente* remetente = obterOuCriarCliente(novoEvento->getRemetente());
//         Cliente* destinatario = obterOuCriarCliente(novoEvento->getDestinatario());

//         // Atualiza as informações do pacote
//         pacote->nomeClienteRemetente = remetente->nome;
//         pacote->nomeClienteDestino = destinatario->nome;
//         pacote->idArmazemAtual = novoEvento->getArmazemDestino(); // Pacote começa no destino do RG

//         // Vincula o ID do pacote ao histórico de cada cliente
//         remetente->pacotesEnviados.push_back(pacote->id);
//         destinatario->pacotesRecebidos.push_back(pacote->id);

//     } else if (tipo == TipoEvento::TR) {
//         // Para um evento de Transferência, atualizamos a localização do pacote
//         // SUPOSIÇÃO: A classe Pacote tem um membro `int idArmazemAtual;`
//         pacote->idArmazemAtual = novoEvento->getArmazemDestino();

//     } else if (tipo == TipoEvento::AR || tipo == TipoEvento::RM || tipo == TipoEvento::UR) {
//         // Para eventos de armazenagem/seção, atualizamos a localização mais específica
//         // SUPOSIÇÃO: A classe Pacote tem membros `int idArmazemAtual;` e `int idSecaoAtual;`
//         pacote->idArmazemAtual = novoEvento->getArmazemDestino();
//         pacote->idSecaoAtual = novoEvento->getSecaoDestino();
//     }
// }














// void SistemaLogistico::consultarPacote(int idPacote){
//     // std::cout << "opa PC | " << idPacote << std::endl;
//     // <dh> PC <identificador pacote>: Histórico do pacote <identificador pacote>.
// };

// void SistemaLogistico::consultarCliente(const std::string& nomeCliente){
//     // std::cout << "opa CL | " << nomeCliente << std::endl;
//     // <dh> CL <nome cliente>: Histórico dos pacotes associados a <nome cliente>.
// };








// void SistemaLogistico::imprimirEventos() {
//     std::cout << "\n--- Imprimindo Todos os Eventos (ordenados por ID do evento) ---\n" << std::endl;
//     // Define uma função lambda para ser usada como callback pelo método percorrerEmOrdem.
//     // Esta função será chamada para cada Evento* na árvore.
//     auto imprimirDetalhesEvento = [](Evento* ev) {
//         if (ev){
//             std::cout << ev->getInfo() << std::endl;
//         };
//     };
//     // Usa o método da árvore para percorrer todos os nós e aplicar a função de impressão.
//     this->eventos.percorrerEmOrdem(imprimirDetalhesEvento);
//     std::cout << "\n--- Fim da Lista de Eventos ---\n" << std::endl;
// }


// // 0000200 PC 003 <consulta 2>
// // 5 <n1 - numero de linhas da resposta da consulta 1>
// // 0000001 EV RG 003 JOAO MARIA 000 003
// // 0000002 EV AR 003 000 002
// // 0000104 EV RM 003 000 002
// // 0000104 EV TR 003 000 002
// // 0000124 EV AR 003 002 003

// // 0300 PC 002 <consulta 4>
// // 7 <n1 - numero de linhas da resposta da consulta 1>
// // 0000080 EV RG 002 PEDRO LUISA 000 003
// // 0000093 EV AR 002 000 002
// // 0000102 EV RM 002 000 002
// // 0000104 EV UR 002 000 002
// // 0000202 EV RM 002 000 002
// // 0000202 EV TR 002 000 002
// // 0000222 EV AR 002 002 003

// // 0000210 CL JOAO <consulta 3>
// // 4 <n1 - numero de linhas da resposta da consulta 1>
// // 0000001 EV RG 003 JOAO MARIA 000 003
// // 0000070 EV RG 007 JOAO JOSE 000 003
// // 0000203 EV TR 003 002 003
// // 0000203 EV TR 007 002 003

// // 0000150 CL LUISA <consulta 1>
// // 6 <n1 - numero de linhas da resposta da consulta 1>
// // 0000006 EV RG 006 LUISA ANDRE 003 002
// // 0000012 EV RG 005 BERNARDO LUISA 002 003
// // 0000080 EV RG 002 PEDRO LUISA 000 003
// // 0000104 EV UR 002 000 002
// // 0000122 EV EN 005 003
// // 0000123 EV EN 006 002


// // <consulta 1>
// // <n1 - numero de linhas da resposta da consulta 1>
// // <linha 1 da resposta a consulta 1>
// // ...
// // <linha n1 da resposta a consulta 1>
// // <consulta 2>
// // ...

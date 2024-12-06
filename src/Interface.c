#include <gtk/gtk.h>
#include <stdlib.h>

char* select_file() {
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    char *filename = NULL;

    // Inicializa o GTK
    gtk_init(NULL, NULL);

    // Cria a janela de seleção de arquivos
    dialog = gtk_file_chooser_dialog_new("Selecione um arquivo",
                                         NULL,
                                         action,
                                         "_Cancelar", GTK_RESPONSE_CANCEL,
                                         "_Abrir", GTK_RESPONSE_ACCEPT,
                                         NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    // Exibe a janela e captura a resposta do usuário
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT) {
        // Obtém o caminho do arquivo selecionado
        filename = gtk_file_chooser_get_filename(chooser);
    }

    // Fecha e destrói a janela de diálogo
    gtk_widget_destroy(dialog);

    // Processa os eventos pendentes para garantir que a janela feche imediatamente
    while (g_main_context_iteration(NULL, FALSE));

    return filename; // Retorna o caminho do arquivo ou NULL se cancelado
}

// Função de callback para manipular a resposta do diálogo
void on_entry_activate(GtkEntry *entry, gpointer user_data) {
    GtkWidget *dialog = GTK_WIDGET(user_data);
    gtk_dialog_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT);
}

char* select_folder_and_create_file() {
    GtkWidget *dialog, *content_area, *entry, *grid, *label;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;
    char *folder_path = NULL;
    char *file_path = NULL;

    // Inicializa o GTK
    gtk_init(NULL, NULL);

    // Cria a janela de seleção de pasta
    dialog = gtk_file_chooser_dialog_new("Selecione uma pasta e insira o nome do arquivo",
                                         NULL,
                                         action,
                                         "_Cancelar", GTK_RESPONSE_CANCEL,
                                         "_Criar Arquivo", GTK_RESPONSE_ACCEPT,
                                         NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    // Adiciona widgets extras usando GtkGrid
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10); // Define espaçamento entre linhas
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10); // Define espaçamento entre colunas
    gtk_widget_set_margin_top(grid, 15); // Margem superior
    gtk_widget_set_margin_bottom(grid, 15); // Margem inferior
    gtk_widget_set_margin_start(grid, 15); // Margem esquerda
    gtk_widget_set_margin_end(grid, 15);   // Margem direita

    // Cria o rótulo e o campo de entrada
    label = gtk_label_new("Digite o nome do arquivo:");
    gtk_widget_set_halign(label, GTK_ALIGN_START); // Alinha o texto à esquerda
    entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 90); // Define largura mínima da entrada

    // Conecta o sinal "activate" do campo de entrada
    g_signal_connect(entry, "activate", G_CALLBACK(on_entry_activate), dialog);

    // Adiciona o rótulo e o campo de entrada ao grid
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(content_area), grid);
    gtk_widget_show_all(dialog);

    // Exibe a janela e captura a resposta do usuário
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT) {
        const char *filename;

        // Obtém o caminho da pasta selecionada
        folder_path = gtk_file_chooser_get_filename(chooser);

        // Obtém o texto do campo de entrada
        filename = gtk_entry_get_text(GTK_ENTRY(entry));

        // Verifica se o nome do arquivo foi inserido e a pasta selecionada
        if (filename && *filename && folder_path) {
            // Aloca memória para o caminho completo do arquivo
            file_path = g_strdup_printf("%s/%s", folder_path, filename);

            // Cria um arquivo vazio na pasta selecionada
            FILE *file = fopen(file_path, "w");
            if (file) {
                fprintf(file, "Arquivo criado com sucesso!\n");
                fclose(file);
            } else {
                g_print("Erro ao criar o arquivo em: %s\n", file_path);
                g_free(file_path);
                file_path = NULL;
            }
        } else {
            g_print("Nome do arquivo ou pasta inválido.\n");
        }

        g_free(folder_path); // Libera o caminho da pasta
    }

    // Fecha e destrói a janela de diálogo
    gtk_widget_destroy(dialog);

    // Processa eventos pendentes para garantir o fechamento imediato da janela
    while (g_main_context_iteration(NULL, FALSE));

    return file_path; // Retorna o caminho do arquivo ou NULL se cancelado/erro
}
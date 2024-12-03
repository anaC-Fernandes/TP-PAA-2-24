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

#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_LINES 1000000  // dataset.txt satır sayısı

int main(int argc, char *argv[]) {
    int rank, size;
    long long local_sum = 0, global_sum = 0;

    MPI_Init(&argc, &argv);  // MPI başlat
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // rank al
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // toplam node/işlem sayısı

    //dataset.txt parçalanıyor
    int chunk = TOTAL_LINES / size; //  Veriyi işlem sayısına göre böl
    int start_line = rank * chunk;  //  Her işleme başlama satırı ata
    int end_line = (rank == size - 1) ? TOTAL_LINES : start_line + chunk;

    int threads = omp_get_max_threads(); //  OpenMP ile kullanılacak çekirdek sayısı

    printf("🔧 [Rank %d] Toplam %d düğümden benim sıram %d\n", rank, size, rank);
    printf("📄 [Rank %d] dataset.txt dosyasından %d ile %d. satırları okuyacağım (%d satır)\n",
           rank, start_line, end_line - 1, end_line - start_line);
    printf("⚙️  [Rank %d] OpenMP ile %d çekirdek kullanılıyor\n", rank, threads);

    double t1 = MPI_Wtime();  // zaman başlat

    FILE *file = fopen("dataset.txt", "r");
    if (!file) {
        fprintf(stderr, "🚨 [Rank %d] dataset.txt açılamadı!\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    char line[64];
    int current_line = 0;
    int values_to_read = end_line - start_line;
    int *values = malloc(values_to_read * sizeof(int));
    int idx = 0;

    while (fgets(line, sizeof(line), file)) {
        if (current_line >= start_line && current_line < end_line) {
            values[idx++] = atoi(line);
        }
        current_line++;
        if (current_line >= end_line) break;
    }
    fclose(file);

    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < values_to_read; i++) {
        local_sum += values[i];
    }
    free(values);

    double t2 = MPI_Wtime();  // zaman bitiş

    printf("✅ [Rank %d] Parçalı toplam = %lld (%.4f saniye sürdü)\n", rank, local_sum, t2 - t1);

    FILE *f = fopen("output.txt", "a");
    if (f) {
        fprintf(f, "[Rank %d] Parçalı toplam = %lld | Süre = %.4f sn\n", rank, local_sum, t2 - t1);
        fclose(f);
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD); // Tüm işlemlerin yerel toplamlarını toplayarak rank 0'a gönder

    if (rank == 0) {
        printf("\n🎯 [Rank 0] Tüm sonuçlar toplandı!\n");
        printf("🌍 Global toplam: %lld\n", global_sum);
        FILE *f = fopen("output.txt", "a");
        if (f) {
            fprintf(f, "🌍 Global toplam: %lld\n", global_sum);
            fclose(f);
        }
    }

    MPI_Finalize();
    return 0;
}

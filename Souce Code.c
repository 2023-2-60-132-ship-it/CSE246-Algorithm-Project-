#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define CITY_COUNT 10   


char cities[CITY_COUNT][20] = {
    "Dhaka", "Chittagong", "Rajshahi", "Khulna", "Sylhet",
    "Barisal", "Rangpur", "Mymensingh", "Comilla", "Narayanganj"
};


int graph[CITY_COUNT][CITY_COUNT] = {
    
    {  0, 10,  0, 30,100,  0,  0,  0, 20, 15}, 
    { 10,  0, 50,  0, 20,  0,  0,  0, 25,  0}, 
    {  0, 50,  0, 20, 10,  0, 40,  0,  0,  0}, 
    { 30,  0, 20,  0, 60, 35,  0,  0,  0,  0}, 
    {100, 20, 10, 60,  0,  0,  0,  0,  0,  0},
    {  0,  0,  0, 35,  0,  0,  0,  0, 30, 25}, 
    {  0,  0, 40,  0,  0,  0,  0, 45,  0,  0}, 
    {  0,  0,  0,  0,  0,  0, 45,  0,  0, 35}, 
    { 20, 25,  0,  0,  0, 30,  0,  0,  0, 10}, 
    { 15,  0,  0,  0,  0, 25,  0, 35, 10,  0} 
};

// ---------------- BFS(Breadth First Search) ----------------
void BFS(int start) {
    int visited[CITY_COUNT] = {0};
    int queue[CITY_COUNT], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS Traversal starting from %s:\n", cities[start]);

    while (front < rear) {
        int current = queue[front++];
        printf("%s ", cities[current]);

        // check all possible neighbours
        for (int i = 0; i < CITY_COUNT; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

// ---------------- DFS(Depth First Search) ----------------
void DFSUtil(int city, int visited[]) {
    visited[city] = 1;
    printf("%s ", cities[city]);

    for (int i = 0; i < CITY_COUNT; i++) {
        if (graph[city][i] && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void DFS(int start) {
    int visited[CITY_COUNT] = {0};
    printf("\nDFS Traversal starting from %s:\n", cities[start]);
    DFSUtil(start, visited);
    printf("\n");
}

// ---------------- Dijkstra (one source -> one destination) ----------------
void DijkstraToAny(int src, int dest) {
    int dist[CITY_COUNT];
    int visited[CITY_COUNT] = {0};
    int parent[CITY_COUNT];

   
    for (int i = 0; i < CITY_COUNT; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < CITY_COUNT - 1; count++) {
        int min = INT_MAX, u = -1;

       
        for (int i = 0; i < CITY_COUNT; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break; 
        visited[u] = 1;

       
        for (int v = 0; v < CITY_COUNT; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        printf("\nNo path from %s to %s\n", cities[src], cities[dest]);
        return;
    }

    printf("\nShortest path from %s to %s (Distance = %d): ",
           cities[src], cities[dest], dist[dest]);

    
    int path[CITY_COUNT], idx = 0, current = dest;
    while (current != -1) {
        path[idx++] = current;
        current = parent[current];
    }

    
    for (int i = idx - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// ---------------- Dijkstra (all cities from a source) ----------------
void DijkstraAll(int src) {
    int dist[CITY_COUNT];
    int visited[CITY_COUNT] = {0};
    int parent[CITY_COUNT];

    for (int i = 0; i < CITY_COUNT; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < CITY_COUNT - 1; count++) {
        int min = INT_MAX, u = -1;
        for (int i = 0; i < CITY_COUNT; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < CITY_COUNT; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nShortest distances from %s:\n", cities[src]);
    for (int i = 0; i < CITY_COUNT; i++) {
        if (dist[i] == INT_MAX) {
            printf("%s -> %s : Unreachable\n", cities[src], cities[i]);
            continue;
        }

        printf("%s -> %s = %d, Path: ", cities[src], cities[i], dist[i]);

        int path[CITY_COUNT], idx = 0, current = i;
        while (current != -1) {
            path[idx++] = current;
            current = parent[current];
        }
        for (int j = idx - 1; j >= 0; j--) {
            printf("%s", cities[path[j]]);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }
}


int getCityIndex(char *name) {
    for (int i = 0; i < CITY_COUNT; i++) {
        if (strcmp(cities[i], name) == 0) return i;
    }
    return -1;
}

void bubbleSort(char arr[CITY_COUNT][20]) {
    char temp[20];
    for (int i = 0; i < CITY_COUNT - 1; i++) {
        for (int j = 0; j < CITY_COUNT - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

int binarySearch(char arr[CITY_COUNT][20], char *target) {
    int low = 0, high = CITY_COUNT - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(arr[mid], target);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void displayCities() {
    printf("\nAvailable cities: ");
    for (int i = 0; i < CITY_COUNT; i++) {
        printf("%s", cities[i]);
        if (i < CITY_COUNT - 1) printf(", ");
    }
    printf("\n");
}

// ---------------- Main ----------------
int main() {
    int choice;
    while (1) {
        printf("\n========== BanglaRoute: Optimized City Navigation for Bangladesh ==========\n");
        printf("1. BFS Traversal\n");
        printf("2. DFS Traversal\n");
        printf("3. Shortest Path to All Cities (Dijkstra)\n");
        printf("4. Shortest Path to Any City (Dijkstra)\n");
        printf("5. Sort Cities (Bubble Sort)\n");
        printf("6. Search City (Binary Search)\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting... Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1: {
                char start[20];
                displayCities();
                printf("Enter starting city: ");
                scanf("%s", start);
                int idx = getCityIndex(start);
                if (idx != -1) BFS(idx);
                else printf("City not found!\n");
                break;
            }
            case 2: {
                char start[20];
                displayCities();
                printf("Enter starting city: ");
                scanf("%s", start);
                int idx = getCityIndex(start);
                if (idx != -1) DFS(idx);
                else printf("City not found!\n");
                break;
            }
            case 3: {
                char start[20];
                displayCities();
                printf("Enter starting city: ");
                scanf("%s", start);
                int idx = getCityIndex(start);
                if (idx != -1) DijkstraAll(idx);
                else printf("City not found!\n");
                break;
            }
            case 4: {
                char start[20], dest[20];
                displayCities();
                printf("Enter starting city: ");
                scanf("%s", start);
                printf("Enter destination city: ");
                scanf("%s", dest);
                int s = getCityIndex(start);
                int d = getCityIndex(dest);
                if (s != -1 && d != -1) DijkstraToAny(s, d);
                else printf("Invalid city names!\n");
                break;
            }
            case 5: {
                char sorted[CITY_COUNT][20];
                for (int i = 0; i < CITY_COUNT; i++)
                    strcpy(sorted[i], cities[i]);
                bubbleSort(sorted);
                printf("\nSorted city list: ");
                for (int i = 0; i < CITY_COUNT; i++)
                    printf("%s ", sorted[i]);
                printf("\n");
                break;
            }
            case 6: {
                char sorted[CITY_COUNT][20], target[20];
                for (int i = 0; i < CITY_COUNT; i++)
                    strcpy(sorted[i], cities[i]);
                bubbleSort(sorted);
                printf("Enter city to search: ");
                scanf("%s", target);
                int pos = binarySearch(sorted, target);
                if (pos != -1)
                    printf("%s found at position %d in sorted list.\n", target, pos + 1);
                else
                    printf("%s not found in the list.\n", target);
                break;
            }
            default:
                printf("Invalid choice! Try again.\n");
        }

    }
    return 0;
}

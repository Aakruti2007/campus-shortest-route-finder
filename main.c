#include <stdio.h>

#define MAX 5
#define INF 9999

int graph[MAX][MAX];
int n = 0;
int source = -1;

int distance[MAX];
int visited[MAX];
int parent[MAX];

/* Enter the campus graph */
void enterGraph()
{
    int i, j;

    printf("\nEnter number of campus locations (maximum 5): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of locations!\n");
        n = 0;
        return;
    }

    printf("\nLocations:\n");
    printf("1. Main Gate\n");
    printf("2. Library\n");
    printf("3. Computer Department\n");
    printf("4. Laboratory\n");
    printf("5. Auditorium\n");

    printf("\nEnter distance between locations.\n");
    printf("Enter 0 if there is no direct connection.\n");

    /* Initialize graph */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
    }

    /* Enter each road only once */
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("Distance from Location %d to Location %d: ",
                   i + 1, j + 1);

            scanf("%d", &graph[i][j]);

            /* Graph is undirected */
            graph[j][i] = graph[i][j];

            if (graph[i][j] == 0)
            {
                graph[i][j] = INF;
                graph[j][i] = INF;
            }
        }
    }

    /* Distance from a location to itself is 0 */
    for (i = 0; i < n; i++)
    {
        graph[i][i] = 0;
    }

    printf("\nCampus graph entered successfully!\n");
}

/* Display adjacency matrix */
void displayMatrix()
{
    int i, j;

    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\n========== ADJACENCY MATRIX ==========\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
            {
                printf("INF\t");
            }
            else
            {
                printf("%d\t", graph[i][j]);
            }
        }

        printf("\n");
    }
}

/* Select source location */
void selectSource()
{
    int choice;

    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\n========== LOCATIONS ==========\n");
    printf("1. Main Gate\n");
    printf("2. Library\n");
    printf("3. Computer Department\n");
    printf("4. Laboratory\n");
    printf("5. Auditorium\n");

    printf("\nEnter source location: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > n)
    {
        printf("Invalid location!\n");
        source = -1;
    }
    else
    {
        source = choice - 1;
        printf("Source selected: Location %d\n", choice);
    }
}

/* Find the vertex with minimum distance */
int findMin()
{
    int min = INF;
    int index = -1;
    int i;

    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0 && distance[i] < min)
        {
            min = distance[i];
            index = i;
        }
    }

    return index;
}

/* Dijkstra's Algorithm */
void dijkstra()
{
    int i, j, u;

    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    if (source == -1)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }

    /* Initialize */
    for (i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    /* Dijkstra's Algorithm */
    for (i = 0; i < n; i++)
    {
        u = findMin();

        if (u == -1)
        {
            break;
        }

        visited[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 &&
                graph[u][j] != INF &&
                distance[u] + graph[u][j] < distance[j])
            {
                distance[j] = distance[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }

    printf("\nShortest distances calculated successfully!\n");
}

/* Print the path */
void printPath(int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%d", vertex + 1);
        return;
    }

    printPath(parent[vertex]);
    printf(" -> %d", vertex + 1);
}

/* Find Shortest Distance */
void findShortestDistance()
{
    int i;

    dijkstra();

    if (source == -1)
    {
        return;
    }

    printf("\n========== SHORTEST DISTANCES ==========\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
        {
            continue;
        }

        if (distance[i] == INF)
        {
            printf("Location %d : Unreachable\n", i + 1);
        }
        else
        {
            printf("Location %d : %d\n", i + 1, distance[i]);
        }
    }
}

/* Display shortest paths */
void displayShortestPaths()
{
    int i;

    dijkstra();

    if (source == -1)
    {
        return;
    }

    printf("\n========== SHORTEST PATHS ==========\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
        {
            continue;
        }

        printf("To Location %d : ", i + 1);

        if (distance[i] == INF)
        {
            printf("No path\n");
        }
        else
        {
            printPath(i);
            printf("\n");
        }
    }
}

/* Display distance from source to all locations */
void displayAllDistances()
{
    int i;

    dijkstra();

    if (source == -1)
    {
        return;
    }

    printf("\n========== DISTANCE FROM SOURCE ==========\n");
    printf("Source Location: %d\n", source + 1);

    for (i = 0; i < n; i++)
    {
        if (distance[i] == INF)
        {
            printf("Location %d : Unreachable\n", i + 1);
        }
        else
        {
            printf("Location %d : %d\n", i + 1, distance[i]);
        }
    }
}

/* Main function */
int main()
{
    int choice;

    printf("========================================\n");
    printf("       CAMPUS SHORTEST ROUTE FINDER\n");
    printf("          Using Dijkstra Algorithm\n");
    printf("========================================\n");

    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source to All Locations\n");
        printf("7. Exit\n");
        printf("===============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                selectSource();
                break;

            case 4:
                findShortestDistance();
                break;

            case 5:
                displayShortestPaths();
                break;

            case 6:
                displayAllDistances();
                break;

            case 7:
                printf("\nProgram ended.\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}
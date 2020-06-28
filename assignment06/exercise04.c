#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000

#define TRUE 1
#define FALSE 0

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define S 0
#define T 1
#define X 2
#define Y 3
#define Z 4

char get_vertex(int vertex)
{
    char cvertex;

    switch (vertex)
    {
    case S:
        cvertex = 'S';
        break;
    case T:
        cvertex = 'T';
        break;
    case X:
        cvertex = 'X';
        break;
    case Y:
        cvertex = 'Y';
        break;
    case Z:
        cvertex = 'Z';
        break;
    default:
        break;
    }

    return cvertex;
}

typedef struct queue
{
    int items[MAX_SIZE];
    int front;
    int rear;
} QUEUE;

QUEUE *create_queue()
{
    QUEUE *queue = malloc(sizeof(QUEUE));
    queue->front = -1;
    queue->rear = -1;

    return queue;
}
void enqueue(QUEUE *queue, int value)
{
    if (queue->rear == MAX_SIZE - 1)
    {
        printf("Full Queue\n");
    }
    else
    {
        if (queue->front == -1)
        {
            queue->front = 0;
        }
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}
int is_empty(QUEUE *queue)
{
    if (queue->rear == -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int dequeue(QUEUE *queue)
{
    int item;

    if (is_empty(queue))
    {
        printf("Empty queue\n");
        item = -1;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear)
        {
            queue->front = queue->rear = -1;
        }
    }

    return item;
}

typedef struct vertex
{
    int vertex;
    int color;
    int d;
    struct vertex *pi;
} VERTEX;
VERTEX vertices[5];

typedef struct node
{
    VERTEX *vertex;
    struct node *next;
} NODE;

typedef struct graph
{
    int num_vertices;
    NODE **adjLists;
    int **weights;
} GRAPH;

void initialize_single_source(GRAPH *graph, int start_vertex)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (i != start_vertex)
        {
            vertices[i].color = WHITE;
            vertices[i].d = INT_MAX;
            vertices[i].pi = NULL;
        }
        else
        {
            vertices[i].color = GRAY;
            vertices[i].d = 0;
            vertices[i].pi = &vertices[i];
        }
    }
}

void relax(int src, int dest, int weight)
{
    if (vertices[dest].d > (vertices[src].d + weight))
    {
        vertices[dest].d = vertices[src].d + weight;
        vertices[dest].pi = &vertices[src];
    }
}

void print_queue(QUEUE *queue)
{
    if (is_empty(queue))
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("Queue items: ");
        for (int i = queue->front; i < queue->rear + 1; i++)
        {
            printf("%c ", get_vertex(queue->items[i]));
        }
        printf("\n");
    }
}

int extract_minimum(QUEUE *queue)
{
    int min = queue->front;
    for (int i = queue->front + 1; i <= queue->rear; i++)
    {

        if (vertices[queue->items[i]].d < vertices[min].d)
        {
            min = i;
        }
    }

    int value = queue->items[min];
    for (int i = min + 1; i <= queue->rear; i++)
    {
        queue->items[i - 1] = queue->items[i];
    }
    queue->rear--;

    vertices[value].color = GRAY;

    return value;
}

void print_path(GRAPH *graph, int start_vertex, VERTEX *vertex)
{
    if (vertex->vertex == start_vertex)
    {
        printf("%c ", get_vertex(start_vertex));
    }
    else if (vertex->pi == NULL)
    {
        printf("No path from %c to %c exists\n", get_vertex(start_vertex), get_vertex(vertex->vertex));
    }
    else
    {
        print_path(graph, start_vertex, vertex->pi);
        printf("%c ", get_vertex(vertex->vertex));
    }
}

void DIJKSTRA(GRAPH *graph, int **weight, int start_vertex, int dest_vertex)
{
    initialize_single_source(graph, start_vertex);
    int set[5];
    int count = 0;
    QUEUE *queue = create_queue();

    for (int i = 0; i < graph->num_vertices; i++)
    {
        enqueue(queue, i);
    }

    for (; !is_empty(queue);)
    {
        int current_vertex = extract_minimum(queue);
        vertices[current_vertex].color = BLACK;
        {
            set[count++] = current_vertex;
            for (NODE *temp_node = graph->adjLists[current_vertex]; temp_node; temp_node = temp_node->next)
            {
                if (temp_node->vertex->color == WHITE)
                {
                    relax(current_vertex, temp_node->vertex->vertex, weight[current_vertex][temp_node->vertex->vertex]);
                }
            }
        }
    }
    printf("Shortest path from the vertex %c to %c: ", get_vertex(dest_vertex), get_vertex(dest_vertex));
    print_path(graph, start_vertex, &vertices[dest_vertex]);
    printf("\n");
}

NODE *create_node(int vertex)
{
    NODE *node = malloc(sizeof(NODE));
    node->vertex = &vertices[vertex];
    node->next = NULL;

    return node;
}

GRAPH *create_graph(int num_vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->num_vertices = num_vertices;
    graph->adjLists = malloc(num_vertices * sizeof(NODE *));

    for (int i = 0; i < num_vertices; i++)
    {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void add_edge(GRAPH *graph, int src, int dest)
{
    NODE *node = create_node(dest);
    node->next = graph->adjLists[src];
    graph->adjLists[src] = node;
}

void create_vertex(void)
{
    vertices[S].vertex = S;
    vertices[T].vertex = T;
    vertices[X].vertex = X;
    vertices[Y].vertex = Y;
    vertices[Z].vertex = Z;
}

void print_d()
{
    printf("------------------------\n");
    printf("        DISTANCE\n");
    printf("------------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("distance to vertex %c: %d\n", get_vertex(vertices[i].vertex), vertices[i].d);
    }
}
void print_pi()
{
    printf("------------------------\n");
    printf("           PI\n");
    printf("------------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("PI of vertex %c: vertex %c\n", get_vertex(vertices[i].vertex), get_vertex((vertices[i].pi)->vertex));
    }
}

int main(void)
{
    GRAPH *graph = create_graph(5);

    create_vertex();

    int **weight = malloc(graph->num_vertices * sizeof(int *));
    for (int i = 0; i < graph->num_vertices; i++)
    {
        weight[i] = malloc(graph->num_vertices * sizeof(int));
    }

    for (int i = 0; i < graph->num_vertices; i++)
    {
        for (int j = 0; j < graph->num_vertices; j++)
        {
            weight[i][j] = -1;
        }
    }

    weight[S][T] = 3;
    weight[S][Y] = 5;
    weight[T][Y] = 2;
    weight[T][X] = 6;
    weight[Y][T] = 1;
    weight[Y][X] = 4;
    weight[Y][Z] = 6;
    weight[X][Z] = 2;
    weight[Z][X] = 7;
    weight[Z][S] = 3;

    add_edge(graph, S, T);
    add_edge(graph, S, Y);
    add_edge(graph, T, Y);
    add_edge(graph, T, X);
    add_edge(graph, Y, T);
    add_edge(graph, Y, X);
    add_edge(graph, Y, Z);
    add_edge(graph, X, Z);
    add_edge(graph, Z, S);
    add_edge(graph, Z, X);

    DIJKSTRA(graph, weight, S, Y);
    DIJKSTRA(graph, weight, S, Z);
    print_d();
    print_pi();

    free(weight);

    return 0;
}
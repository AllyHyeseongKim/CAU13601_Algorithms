#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000

#define TRUE 1
#define FALSE 0

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define R 0
#define S 1
#define T 2
#define U 3
#define V 4
#define W 5
#define X 6
#define Y 7

char get_vertex(int vertex)
{
    char cvertex;

    switch (vertex)
    {
    case R:
        cvertex = 'R';
        break;
    case S:
        cvertex = 'S';
        break;
    case T:
        cvertex = 'T';
        break;
    case U:
        cvertex = 'U';
        break;
    case V:
        cvertex = 'V';
        break;
    case W:
        cvertex = 'W';
        break;
    case X:
        cvertex = 'X';
        break;
    case Y:
        cvertex = 'Y';
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
VERTEX vertices[8];

typedef struct node
{
    VERTEX *vertex;
    struct node *next;
} NODE;

typedef struct graph
{
    int num_vertices;
    NODE **adjLists;
} GRAPH;
/*
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
*/
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

void BFS(GRAPH *graph, int start_vertex)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (vertices[i].vertex != start_vertex)
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
    QUEUE *queue = create_queue();

    enqueue(queue, start_vertex);

    for (; !is_empty(queue);)
    {
        print_queue(queue);

        int current_vertex = dequeue(queue);

        for (NODE *temp_node = graph->adjLists[current_vertex]; temp_node; temp_node = temp_node->next)
        {
            if (temp_node->vertex->color == WHITE)
            {
                vertices[temp_node->vertex->vertex].color = GRAY;
                vertices[temp_node->vertex->vertex].d = vertices[current_vertex].d + 1;
                vertices[temp_node->vertex->vertex].pi = &vertices[current_vertex];
                enqueue(queue, temp_node->vertex->vertex);
            }
        }

        vertices[graph->adjLists[current_vertex]->vertex->vertex].color = BLACK;
    }

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

    node = create_node(src);
    node->next = graph->adjLists[dest];
    graph->adjLists[dest] = node;
}

void create_vertex(void)
{
    vertices[R].vertex = R;
    vertices[S].vertex = S;
    vertices[T].vertex = T;
    vertices[U].vertex = U;
    vertices[V].vertex = V;
    vertices[W].vertex = W;
    vertices[X].vertex = X;
    vertices[Y].vertex = Y;
}

void print_d()
{
    printf("------------------------\n");
    printf("        DISTANCE\n");
    printf("------------------------\n");
    for (int i = 0; i < 8; i++)
    {
        printf("distance to vertex %c: %d\n", get_vertex(vertices[i].vertex), vertices[i].d);
    }
}
void print_pi()
{
    printf("------------------------\n");
    printf("           PI\n");
    printf("------------------------\n");
    for (int i = 0; i < 8; i++)
    {
        printf("PI of vertex %c: vertex %c\n", get_vertex(vertices[i].vertex), get_vertex((vertices[i].pi)->vertex));
    }
}

int main(void)
{
    GRAPH *graph = create_graph(8);

    create_vertex();

    add_edge(graph, R, S);
    add_edge(graph, R, V);
    add_edge(graph, S, W);
    add_edge(graph, W, T);
    add_edge(graph, W, X);
    add_edge(graph, T, X);
    add_edge(graph, T, U);
    add_edge(graph, X, W);
    add_edge(graph, X, Y);
    add_edge(graph, U, Y);

    BFS(graph, S);

    print_d();
    print_pi();
}
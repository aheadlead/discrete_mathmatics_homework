#include <stdio.h>
#define MAX_VERTEX_NUMEBR 1000

FILE *in, *out;
int vertex_number = 0, edge_number = 0;
int base_vertex_number = 0;
int g[MAX_VERTEX_NUMEBR][MAX_VERTEX_NUMEBR] = {{0}};

int stack[MAX_VERTEX_NUMEBR] = {0};
int stack_top = 0;

int is_connected_graph()
{
    int i;
    int queue[MAX_VERTEX_NUMEBR],
        front=0,
        back=0;
    int is_visit[MAX_VERTEX_NUMEBR] = {0}, visited_counter = 1;
    queue[front++] = 0;
    is_visit[0] = 1;
    while (front != back)
    {
        for (i=0; i<vertex_number; ++i)
        {
            if (g[queue[back]][i] == 1 && is_visit[i] == 0)
            {
                is_visit[i] = 1;
                queue[front++] = i;
                visited_counter++;
            }
        }
        back++;
    }
    return vertex_number == visited_counter;
}

void euler(int current_vertex)
{
    int next_vertex, i;
    // bridge_v means a vertex which is linked to current_vertex and the edge from current_vertex to bridge_v is a bridge.
    int bridge_v = -1, tmp; 
    if (current_vertex == base_vertex_number &&
            stack_top == edge_number)
    {
        fprintf(out, "%d", base_vertex_number);
        for (i=1; i<stack_top; ++i)
            fprintf(out, " -> %d", stack[i]);
        fprintf(out, "-> %d\n", base_vertex_number);
        return;
    }

    stack[stack_top++] = current_vertex;

    // find bridge
    for (next_vertex=0; next_vertex<vertex_number; ++next_vertex)
    {
        if (g[current_vertex][next_vertex] == 1)
        {
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 0;
            tmp = is_connected_graph();
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 1;
            if (tmp == 0)
            {
                bridge_v = next_vertex;
                break;
            }
        }
    }

    for (next_vertex=0; next_vertex<vertex_number; ++next_vertex)
    {
        if (g[current_vertex][next_vertex] == 1 && next_vertex != bridge_v)
        {
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 0;
            euler(next_vertex);
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 1;
        }
    }

    if (bridge_v != -1)
    {
        g[current_vertex][bridge_v] = g[bridge_v][current_vertex] = 0;
        euler(bridge_v);
    }

    stack_top--;
    return;
}

int main()
{
    int i, a, b;

    in = fopen("input.txt", "r");
    fscanf(in, "%d%d", &vertex_number, &edge_number);
    fscanf(in, "%d", &base_vertex_number);
    for (i=0; i<edge_number; ++i)
    {
        fscanf(in, "%d%d", &a, &b);
        g[a][b] = g[b][a] = 1;
    }
    fclose(in);
    
    out = fopen("output.txt", "w");
    euler(base_vertex_number);
    fclose(out);

    return 0;
}

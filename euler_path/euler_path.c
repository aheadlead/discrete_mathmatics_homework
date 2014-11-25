/*
 * 算法：
 *      对于图G(V, E)
 *      1   任取一点v0∈V(G), 令P0=v0;
 *      2   设Pi=v0 e1 v1 e1 ... ei vi已经行遍，按下面方法从E(G)-{e1, e2, ..., ei}中选取e(i+1);
 *          a   e(i+1)与vi相关联;
 *          b   除非无别的边可供行遍，否则e(i+1)不应该为Gi=G-{e1, e2, ..., ei}中的桥
 *      3   当2不能再进行时，算法停止
 *
 *      桥的判定：
 *          使用一个数组Deg记录每个点的度数，Deg[i]表示编号为i的点的度数。
 *          每走到一条边时，把这个边所关联的点的度数减一。
 *          判定边e是否为桥时，先去掉边e，
 *          并对剩余的图G进行广度优先搜索，如果能遍历全图，说明边e不是桥，反之亦然。
 *
 * 输入格式：
 *      第一行有两个整数分别为顶点数vertex_number和边数edge_number，空格隔开；
 *      第二行是一个整数代表从何点开始寻找欧拉回路；
 *      下有edge_number行，表示边，每行有关联边的两个点的编号，空格隔开。
 *
 * 输出格式：
 *      
 * 样例：
 *      A.  input:
 *              4 4
 *              0
 *              0 1
 *              1 2
 *              2 3
 *              3 0
 *          output:
 *              0 -> 1 -> 2 -> 3-> 0
 *      B.  input:
 *              4 5
 *              0
 *              0 1
 *              1 2
 *              2 3
 *              3 0
 *              0 2
 *          output:
 *              None
 *      C.  input:
 *              4 3
 *              0
 *              0 1
 *              1 2
 *              2 0
 *          output:
 *              0 -> 1 -> 2-> 0
 *      D.  input:
 *              5 7
 *              0
 *              0 1
 *              0 3
 *              1 2
 *              1 3
 *              1 4
 *              2 3
 *              3 4
 *          output:
 *              0 -> 1 -> 2 -> 3 -> 1 -> 4 -> 3-> 0
 *
 *  编译环境
 *      OS X 10.10 Yosemite 
 *
 *      Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
 *      Apple LLVM version 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
 *      Target: x86_64-apple-darwin14.0.0
 *      Thread model: posix
 *
 *  心得体会：
 *      看似容易的事情，做起来还是不容易啊。  
 *      须菩提。若有善男子善女人。初日分(fèn)以恒河沙等身布施。中日分复以恒河沙等身布施。后日分亦以恒河沙等身布施。如是无量百千万亿劫。以身布施。若复有人闻此经典。信心不逆。其福胜彼。何况书写受持读诵。为人解说。
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUMEBR 1000

FILE *in, *out;
int vertex_number = 0, edge_number = 0;
int base_vertex_number = 0;
int g[MAX_VERTEX_NUMEBR][MAX_VERTEX_NUMEBR] = {{0}};
int Deg[MAX_VERTEX_NUMEBR] = {0};
int non_zero_degree_vertex_number = 0;

int stack[MAX_VERTEX_NUMEBR] = {0};
int stack_top = 0;

int is_connected_graph()
{
    // BFS判连通图
    int i, j;
    int queue[MAX_VERTEX_NUMEBR],
        front=0,
        back=0;
    int is_visit[MAX_VERTEX_NUMEBR] = {0}, visited_counter = 1;
    for (j=0; j<vertex_number; ++j)
    {
        if (Deg[j] <= 0)
            continue;
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
        if (non_zero_degree_vertex_number == visited_counter)
            return 1;
    }
    return 0;
}

void euler(int current_vertex)
{
    int next_vertex, i;
    // bridge_v存有一个顶点的编号，这个顶点和当前的顶点所关联的边，构成了一个桥。（如果桥存在的话，否则为-1）
    int bridge_v = -1, tmp; 
    if (current_vertex == base_vertex_number &&
            stack_top == edge_number)
    {
        // 找到了欧拉回路并输出
        fprintf(out, "%d", base_vertex_number);
        for (i=1; i<stack_top; ++i)
            fprintf(out, " -> %d", stack[i]);
        fprintf(out, "-> %d\n", base_vertex_number);
        exit(0);
    }

    stack[stack_top++] = current_vertex; // 记录欧拉回路

    // 找桥
    for (next_vertex=0; next_vertex<vertex_number; ++next_vertex) // 枚举与current_vertex关联的边
    {
        if (g[current_vertex][next_vertex] == 1)
        {
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 0; // 删边
            Deg[current_vertex]--;
            Deg[next_vertex]--;
            tmp = is_connected_graph();
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 1; 
            Deg[current_vertex]++;
            Deg[next_vertex]++;
            if (tmp == 0) 
            {
                // 如果是桥
                bridge_v = next_vertex;
                break;
            }
        }
    }

    for (next_vertex=0; next_vertex<vertex_number; ++next_vertex) // 枚举欧拉路径的下一个顶点
    {
        if (g[current_vertex][next_vertex] == 1 && next_vertex != bridge_v) // 尽量不走桥
        {
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 0;
            Deg[current_vertex]--;
            Deg[next_vertex]--;
            euler(next_vertex);
            g[current_vertex][next_vertex] = g[next_vertex][current_vertex] = 1;
            Deg[current_vertex]++;
            Deg[next_vertex]++;
        }
    }

    if (bridge_v != -1) // 实在不行再走桥
    {
        g[current_vertex][bridge_v] = g[bridge_v][current_vertex] = 0;
        Deg[current_vertex]--;
        Deg[bridge_v]--;
        euler(bridge_v);
    }

    stack_top--;
    return;
}

int main()
{
    int i, a, b;

    // 读入文件
    in = fopen("input.txt", "r");
    fscanf(in, "%d%d", &vertex_number, &edge_number);
    fscanf(in, "%d", &base_vertex_number);
    for (i=0; i<edge_number; ++i)
    {
        fscanf(in, "%d%d", &a, &b);
        g[a][b] = g[b][a] = 1;
        // 统计度数
        Deg[a]++;
        Deg[b]++;
    }
    fclose(in);

    // 计算度数不为零的顶点数
    for (i=0; i<vertex_number; ++i)
    {
        if (Deg[i] > 0)
        {
            non_zero_degree_vertex_number++;
        }
    }
    
    out = fopen("output.txt", "w");
    // 查找欧拉回路
    euler(base_vertex_number);
    fprintf(out, "None");
    fclose(out);

    return 0;
}

## 习题4

### 1. 验证$SO(3),SE(3)$和$Sim(3)$关于乘法成群

对于集合和运算，群$G=(A,\cdot)$满足下述四个条件：

1. 封闭性：$\forall a_1,a_2\in A$   $a_1\cdot a_2\in A$
2. 结合律：$\forall a_1,a_2,a_3\in A$，  $(a_1\cdot a_2)\cdot a_3=a_1\cdot(a_2\cdot a_3)$
3. 幺元：$\exist a_0\in A$， $s.t.\ \forall a\in A$， $a_0\cdot a=a\cdot a_0=a$
4. 逆：$\forall a\in A$，$\exist a^{-1}\in A$，$s.t.\ a\cdot a^{-1}=a_0$

① 验证$G=(SO(3),\cdot)$

1. 封闭性：$(R_1R_2)(R_1R_2)^T=R_1R_2R_2^TR_1^T=I$，$det(R_1R_2)=det(R_1)det(R_2)=1$。所以$R_1R_2\in SO(3)$
2. 结合律：矩阵乘法的性质
3. 幺元：单位矩阵 $I=\begin{bmatrix}1&0&0\\0&1&0\\ 0& 0&1\end{bmatrix}$
4. 逆：$R$的逆就是$R^T$

② 验证$G(SE(3), \cdot)$

1. 封闭性：
   $$
   \begin{bmatrix} R_1&t_1\\ 0^T &1\end{bmatrix}\begin{bmatrix} R_2&t_2\\ 0^T &1\end{bmatrix}=\begin{bmatrix} R_1R_2&R_1t_2+t_1\\ 0^T &1\end{bmatrix}
   $$
   显然$R_1R_2\in SO(3),R_1t_2+t_1\in R^3$

2. 结合律：矩阵乘法的性质

3. 幺元：单位矩阵 $I=\begin{bmatrix}1&0&0&0\\0&1&0&0\\ 0& 0&1&0 \\ 0&0&0&1\end{bmatrix}$

4. 逆：等于证明$T$存在逆，其实非常容易知道每列线性独立，所以存在逆（因为$R$存在逆，所以前面3列线性独立，又因为最后一列无法由前面三列线性表示，所以4列均线性独立）

③ 验证$G(Sim(3), \cdot)$

1. 封闭性：
   $$
   \begin{bmatrix} sR_1&t_1\\ 0^T &1\end{bmatrix}\begin{bmatrix} sR_2&t_2\\ 0^T &1\end{bmatrix}=\begin{bmatrix} s^2R_1R_2&sR_1t_2+t_1\\ 0^T &1\end{bmatrix}
   $$
   显然$R_1R_2\in SO(3),sR_1t_2+t_1\in R^3$

2. 结合律：矩阵乘法的性质

3. 幺元：单位矩阵 $I=\begin{bmatrix}1&0&0&0\\0&1&0&0\\ 0& 0&1&0 \\ 0&0&0&1\end{bmatrix}$

4. 逆：等于证明$T$存在逆，其实非常容易知道每列线性独立，所以存在逆（因为$R$存在逆，所以前面3列线性独立，又因为最后一列无法由前面三列线性表示，所以4列均线性独立）

### 2. 验证$(R^3,R,\times)$构成李代数

李代数由一个集合$V$，一个数域$F$和一个二元运算符$[,]$组成。如果它们满足以下几条性质，则称$(V,F,[,])$为一个李代数，记做$\mathfrak{g}$：

1. 封闭性：$\forall X,Y\in V,[X,Y]\in V$

2. 双线性：$\forall X,Y,Z\in V,\ a,b\in F$，有：
   $$
   [aX+bY,Z]=a[X,Z]+b[Y,Z],\quad [Z,aX+bY]=a[Z,X]+b[Z,Y]
   $$

3. 自反性：$\forall X\in V, [X,X]=0$

4. 雅克比等价：$\forall X,Y,Z\in V$, $[X,[Y,Z]]+[Z,[X,Y]]+[Y,[Z,X]]=0$

下面令$V=R^3, F=R, [,]=\times $：（请先了解[叉积](https://zh.wikipedia.org/wiki/%E5%8F%89%E7%A7%AF)的性质）

1. 封闭性很明显，因为叉积与另两个向量均垂直，但维数还是三维
2. 双线性，叉积本身性质
3. 自反性：叉积本身性质
4. 雅克比等价：$D=X\times (Y\times Z)+Z\times (X\times Y)+Y\times (Z\times X)$，这条式子的含义是什么呢？其实非常简单，就是$D$落在$Y,Z$构成的平面，也落在$X,Y$构成的平面，也落在$Z,X$够成的平面。而对于任意的$X,Y,Z$它们两两构成的平面的交集也就只有0这个向量了。（可以参考：[叉乘不满足结合律！！！](https://www.zhihu.com/question/29671351)）

### 3. 验证$\mathfrak{so}(3)$和$\mathfrak{se}(3)$满足李代数要求的性质

① 验证$\mathfrak{so}(3)$

令$V=R^{3}, F=R, [\phi_1,\phi_2]=(\Phi_1\Phi_2-\Phi_2\Phi_1)^{\lor} $：

1. 封闭性：（假设$\phi_1=[a_1,a_2,a_3]$，$\phi_2=[b_1,b_2,b_3]$）
   $$
   (\Phi_1\Phi_2-\Phi_2\Phi_1)=\begin{bmatrix}-a_3b_3-a_2b_2&a_2b_1&a_3b_1\\ a_1b_2&-a_3b_3-a_1b_1&a_3b_2\\ a_1b_3&a_2b_3& -a_2b_2-a_1b_1\end{bmatrix}-\\ \begin{bmatrix}-a_3b_3-a_2b_2&a_1b_2&a_1b_3\\ a_2b_1&-a_3b_3-a_1b_1&a_2b_3\\ a_3b_1&a_3b_2& -a_2b_2-a_1b_1\end{bmatrix}=\\ \begin{bmatrix}0&a_2b_1-a_1b_2&a_3b_1-a_1b_3\\ a_1b_2-a_2b_1&0&a_3b_2-a_2b_3\\ a_1b_3-a_3b_1&a_2b_3-a_3b_2& 0\end{bmatrix}
   $$
   所以也为反对称矩阵，因此$(\Phi_1\Phi_2-\Phi_2\Phi_1)^{\lor}\in R^3$

2. 双线性：
   $$
   [a\phi_1+b\phi_2,\phi_3]^{\land}=(a\Phi_1+b\Phi_2)\Phi_3-\Phi_3(a\Phi_1+b\Phi_2)\\=a(\Phi_1\Phi_3-\Phi_3\Phi_1)+b(\Phi_2\Phi_3-\Phi_3\Phi_2)=a[\phi_1,\phi_3]^{\land}+b[\phi_2,\phi_3]^\land \\
   [\phi_3, a\phi_1+b\phi_2]^{\land}=\Phi_3(a\Phi_1+b\Phi_2)-(a\Phi_1+b\Phi_2)\Phi_3\\=a(\Phi_3\Phi_1-\Phi_1\Phi_3)+b(\Phi_3\Phi_2-\Phi_2\Phi_3)=a[\phi_3,\phi_1]^{\land}+b[\phi_3,\phi_2]^\land
   $$
   所以得证

3. 自反性：$[\phi,\phi]=(\Phi\Phi-\Phi\Phi)^\or=0$

4. 雅克比等价：
   首先我们知道：$[\phi_1,[\phi_2,\phi_3]]=(\Phi_1(\Phi_2\Phi_3-\Phi_3\Phi_2)-(\Phi_2\Phi_3-\Phi_3\Phi_2)\Phi_1)^\lor$
   所以存在下述关系：
   $$
   ([\phi_1,[\phi_2,\phi_3]]+[\phi_3,[\phi_1,\phi_2]]+[\phi_2,[\phi_3,\phi_1]])^{\land}=[\phi_1,[\phi_2,\phi_3]]^{\land}+[\phi_3,[\phi_1,\phi_2]]^{\land}+[\phi_2,[\phi_3,\phi_1]]^{\land}\\=\Phi_1(\Phi_2\Phi_3-\Phi_3\Phi_2)-(\Phi_2\Phi_3-\Phi_3\Phi_2)\Phi_1+\Phi_3(\Phi_1\Phi_2-\Phi_2\Phi_1)-(\Phi_1\Phi_2-\Phi_2\Phi_1)\Phi_3+\\\Phi_2(\Phi_3\Phi_1-\Phi_1\Phi_3)-(\Phi_3\Phi_1-\Phi_1\Phi_3)\Phi_2=0
   $$
   所以得证

② 验证$\mathfrak{se}(3)$

令$V=R^{6}, F=R, [\xi_1,\xi_2]=(\xi_1^\land\xi_2^\land-\xi_2^\land\xi_1^\land)^{\lor} $：

1. 封闭性：
   $$
   (\xi_1^\land\xi_2^\land-\xi_2^\land\xi_1^\land)=\begin{bmatrix} \phi_1^\land&\rho_1\\0^T&0\end{bmatrix}\begin{bmatrix} \phi_2^\land&\rho_2\\0^T&0\end{bmatrix}-\begin{bmatrix} \phi_2^\land&\rho_2\\0^T&0\end{bmatrix}\begin{bmatrix} \phi_1^\land&\rho_1\\0^T&0\end{bmatrix}\\=\begin{bmatrix} \phi_1^\land \phi_2^\land -\phi_2^\land \phi_1^\land &\phi_1^\land\rho_2-\phi_2^\land\rho_1\\0^T&0\end{bmatrix}
   $$
   因为$(\phi_1^\land \phi_2^\land -\phi_2^\land\phi_1^\land)^\lor\in\mathfrak{so}(3)$，所以得证

2. 双线性：（令$\Xi=\xi^\land$）
   $$
   [a\xi_1+b\xi_2,\xi_3]^{\land}=(a\Xi_1+b\Xi_2)\Xi_3-\Xi_3(a\Xi_1+b\Xi_2)\\=a(\Xi_1\Xi_3-\Xi_3\Xi_1)+b(\Xi_2\Xi_3-\Xi_3\Xi_2)=a[\xi_1,\xi_3]^{\land}+b[\xi_2,\xi_3]^\land \\
   [\xi_3, a\xi_1+b\xi_2]^{\land}=\Xi_3(a\Xi_1+b\Xi_2)-(a\Xi_1+b\Xi_2)\Xi_3\\=a(\Xi_3\Xi_1-\Xi_1\Xi_3)+b(\Xi_3\Xi_2-\Xi_2\Xi_3)=a[\xi_3,\xi_1]^{\land}+b[\xi_3,\xi_2]^\land
   $$
   所以得证

3. 自反性：$[\xi,\xi]=(\Xi\Xi-\Xi\Xi)^\or=0$

4. 雅克比等价：
   首先我们知道：$[\xi_1,[\xi_2,\xi_3]]=(\Xi_1(\Xi_2\Xi_3-\Xi_3\Xi_2)-(\Xi_2\Xi_3-\Xi_3\Xi_2)\Xi_1)^\lor$
   所以存在下述关系：
   $$
   ([\xi_1,[\xi_2,\xi_3]]+[\xi_3,[\xi_1,\xi_2]]+[\xi_2,[\xi_3,\xi_1]])^{\land}=[\xi_1,[\xi_2,\xi_3]]^{\land}+[\xi_3,[\xi_1,\xi_2]]^{\land}+[\xi_2,[\xi_3,\xi_1]]^{\land}\\=\Xi_1(\Xi_2\Xi_3-\Xi_3\Xi_2)-(\Xi_2\Xi_3-\Xi_3\Xi_2)\Xi_1+\Xi_3(\Xi_1\Xi_2-\Xi_2\Xi_1)-(\Xi_1\Xi_2-\Xi_2\Xi_1)\Xi_3+\\\Xi_2(\Xi_3\Xi_1-\Xi_1\Xi_3)-(\Xi_3\Xi_1-\Xi_1\Xi_3)\Xi_2=0
   $$
   所以得证

### 4. 验证性质（4.20）和（4.21）

① 性质（4.20）

不妨假设$a=[x,y,z]^T$，且$x^2+y^2+z^2=1$。那么：
$$
aa^T=\begin{bmatrix} x\\y\\z\end{bmatrix}\begin{bmatrix} x&y&z\end{bmatrix}=\begin{bmatrix}x^2&xy&xz\\xy&y^2&yz\\xz&yz&z^2 \end{bmatrix}\\
a^\land a^\land=\begin{bmatrix}0&-z&y\\z&0&-x\\-y&x&0\end{bmatrix}\begin{bmatrix}0&-z&y\\z&0&-x\\-y&x&0 \end{bmatrix}=\begin{bmatrix}x^2-1&xy&xz\\xy&y^2-1&yz\\xz&yz&z^2-1 \end{bmatrix}=aa^T-I
$$
所以得证。

② 性质（4.21）
$$
a^\land a^\land a^\land=\begin{bmatrix}x^2-1&xy&xz\\xy&y^2-1&yz\\xz&yz&z^2-1 \end{bmatrix}\begin{bmatrix}0&-z&y\\z&0&-x\\-y&x&0 \end{bmatrix}=\begin{bmatrix}0&z&-y\\-z&0&x\\y&-x&0 \end{bmatrix}=-a^\land
$$
所以得证。

### 5. 证明：$Rp^{\land}R^T=(Rp)^{\land}$

① 最直接的方式就是两边都采用具体的形式展开，比较是不是即可。（写起来很长，就略了。）

② 左边很容易发现为反对称矩阵：
$$
(Rp^\land R^T)^T=R(p^\land)^TR=-Rp^\land R
$$
下面我们先给出具体的形式：
$$
R=\begin{bmatrix} r_{11}&r_{12}&r_{13}\\r_{21}&r_{22}&r_{23}\\r_{31}&r_{32}&r_{33}\end{bmatrix}=\begin{bmatrix} R_{1}&R_{2}&R_{3}\end{bmatrix} \quad p=\begin{bmatrix} x\\y\\z\end{bmatrix}
$$

1. 左边：
   $$
   \begin{bmatrix} R_{1}&R_{2}&R_{3}\end{bmatrix} \begin{bmatrix} 0&-z&y\\z&0&-x\\-y&x&0\end{bmatrix}\begin{bmatrix} R_{1}^T\\R_{2}^T\\R_{3}^T\end{bmatrix}\\=z(R_2R_1^T-R_1R_2^T)+x(R_{3}R_2^T-R_2R_3^T)+y(R_1R_3^T-R_3R_1^T)
   $$

2. 右边：
   $$
   Rp=xR_1+yR_2+zR_3
   $$
   因为我们已经知道左边为反对称矩阵，因此我们只需检查3个位置的值即可（12, 13, 23位置）

3. 下边以$i=1,j=2$为例（其他两个位置同样的方式）
   左边矩阵在$i=1,j=2$的值：
   $$
   z(r_{11}r_{22}-r_{21}r_{12})+x(r_{13}r_{22}-r_{23}r_{12})+y(r_{11}r_{23}-r_{21}r_{13})\\=-zr_{33}-xr_{31}-yr_{32}
   $$

   > 上述用了正交矩阵的性质：$r_{ij}=det(R_{ij})$

   右边矩阵在$i=1,j=2$的值：
   $$
   -zr_{33}-xr_{31}-yr_{32}
   $$
   所以左边=右边，得证。

### 6. 证明：$Rexp(p^{\land})R^T=exp((Rp)^{\land})$

>该式称为$SO(3)$上的伴随性质，同样地，在$SE(3)$上亦有伴随性质：
>$$
>Texp(\xi^\land)T^{-1}=exp((Ad(T)\xi)^\land)
>$$
>其中：
>$$
>Ad(T)=\begin{bmatrix} R& t^\land R\\ 0&R\end{bmatrix}
>$$
>

> 参考[Derivation of Adjoint for SO(3)](https://math.stackexchange.com/questions/2190603/derivation-of-adjoint-for-so3)，[Ethan Eade](http://www.ethaneade.org/lie.pdf)

1. 先对两边同时取$log$操作：
   左边：
   $$
   \log(R\exp(p^\land)R^T)=Rp^\land R^T
   $$

   > 这条式子个人不知道怎么推出来，[logarithm](https://en.wikipedia.org/wiki/Logarithm_of_a_matrix)应该需要对角矩阵才行吧？

   右边：
   $$
   \log(\exp((Rp)^\land))=(Rp)^\land
   $$

2. 那么假设$Rp^\land R^T=(Rp)^\land$，它代表的含义其实也是蛮明确的：反旋转+叉积+旋转 = 旋转后再叉积。下面我们不妨将上述操作作用在一个向量$v$上面：
   右边乘$v$：
   $$
   (Rp)^\land v=(Rp)\times v=Rp\times (RR^T v)=R[p\times (R^Tv)]=Rp^\land R^T v
   $$
   等于左边。所以得证。

### 7. 仿照左扰动的推导，推导$SO(3)$和$SE(3)$在右扰动下的导数

① $SO(3)$
$$
\frac{\partial(Rp)}{\partial \varphi}=\lim_{\varphi\to 0}\frac{\exp(\phi^\land)\exp(\varphi^\land)p-\exp(\phi^\land)p}{\varphi}\approx \lim_{\varphi\to 0}\frac{\exp(\phi^\land)(I+\varphi^\land)p-\exp(\phi^\land)p}{\varphi}\\=\lim_{\varphi\to 0}\frac{\exp(\phi^\land)\varphi^\land p}{\varphi}=\lim_{\varphi\to 0}\frac{R\varphi^\land p}{\varphi}=\lim_{\varphi\to 0}\frac{-Rp^\land\varphi}{\varphi}=-Rp^\land
$$
② $SE(3)$
$$
\frac{\partial(Tp)}{\partial \delta\xi}=\lim_{\delta\xi\to 0}\frac{\exp(\xi^\land)\exp(\delta\xi^\land)p-\exp(\xi^\land)p}{\delta\xi}\approx \lim_{\delta\xi\to 0}\frac{\exp(\xi^\land)\exp(I+\delta\xi^\land)p-\exp(\xi^\land)p}{\delta\xi}\\=\lim_{\delta\xi\to 0}\frac{\exp(\xi^\land)\delta\xi^\land p}{\delta\xi}=\lim_{\delta\xi\to 0}\frac{\begin{bmatrix}R&t\\ 0^T &1\end{bmatrix}\begin{bmatrix}\delta\phi^\land&\delta \rho\\ 0^T &1\end{bmatrix}\begin{bmatrix}p\\ 1\end{bmatrix}}{\delta\xi}=\lim_{\delta\xi\to 0}\frac{\begin{bmatrix}R\delta\phi^\land p+R\delta \rho\\ 0^T\end{bmatrix}}{\delta\xi}
$$
再进一步推导之前，先说一下：① $Tp\in R^{4\times 1}, \delta\xi\in R^{6\times 1}$（因为有6个变量，所以$\delta\xi$才为6维）。所以结果应该为$4\times 6$ ② 下述认为前三维为位移，后三维为旋转（即前面三维与$\rho$相关，后面三维与$\phi$相关）

进一步推导：
$$
\frac{\partial(Tp)}{\partial \delta\xi}=\lim_{\delta\xi\to 0}\frac{\begin{bmatrix}R\delta\phi^\land p+R\delta p\\ 0^T\end{bmatrix}}{\delta\xi}=\begin{bmatrix}-Rp^\land &W \\ 0^T&0^T\end{bmatrix}
$$
其中的$W$为矩阵$R$按列和的转置。

### 8. 搜索cmake的find_package指令是如何运作的。它有那些可选的参数？为了让cmake找到某个库，需要哪些先决条件？

TODO


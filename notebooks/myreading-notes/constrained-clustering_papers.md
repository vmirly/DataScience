
Constrained KMeans with Background Knowledge
===

 * Traditionally, clustering is known as usupervised learning fashion
 * Often some background knowledge exists
 * Integrate background knowledge and clustering algorithms

 * **COBWEB (Fisher, 1987)**

#### Contributions
 * Modified k-means to account for background knowledge in form of instance-level constraints
 * Applying COBWEB to real-world dataset

## COP K-means Algorithm

COPKmeans(Dataset $D$, $ML$ constraints, $CL$ constraints)
  1. Let $c_1, .. c_k$ be initial centroids
  2. Assign each data point to its closest centroid such that 
    * it does not violate ML constraints
    * it does not violate CL constraints
    * if no such cluster is found, clustering has failed
  3. Update the new cluster centroids by averaging ffeature vectors of the cluster members

#### Performance evaluation

 * Rand index
 * Held-out: to see if contraints generalize well or not
   * 10-fold cross validation
   * Generate random constraints in 9 folds
   * Cluster the entire dataset
   * Evaluate the clustering solution on 10th fold


Active Semi-Supervision for Pairwise Constrained Clustering
===

 * $\mathcal{M}$: set of must-link constraints
 * $\mathcal{C}$: set of cannot-link constraints
 * $W$: the weight of each must-link constraint
 * $\bar{W}$: the weight of each cannot constraint
 
 * **defining the cost:**
   * if $(x_i,x_j)\in \mathcal{M}$ then the cost is $w_{ij}\mathbb{1}(l_i \ne l_j)$
   * if $(x_i,x_j)\in \mathcal{C}$ then the cost is $\bar{w}_{ij}\mathbb{1}(l_i = l_j)$
   $$\displaystyle \mathcal{J}_{pckm} = \frac{1}{2} \sum_{x_i\in \mathcal{X}} \|x_i - \mu_{l_i}\|^2 \\ + \sum_{(x_i,x_j)\in \mathcal{M}}w_{ij}\mathbb{1}(l_i \ne l_j) \\ +\sum_{(x_i,x_j)\in \mathcal{C}}\bar{w}_{ij}\mathbb{1}(l_i = l_j)$$

$\mathcal{O}$


```python

```

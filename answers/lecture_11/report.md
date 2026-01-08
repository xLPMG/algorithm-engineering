# Report on Exam Assignments - Lecture 11

## Task 1

**Select one slide from the lecture, research more about the topic, and report on it.**

For this report, I'd like to talk about a very recent topic which is and will stay relevant even in the coming years: 3D NAND Flash Memory. I'm not quite sure to which slide this fits best, but I would assume slide 4 (introduction of NAND memory and cell types) or slide 8 where a 2D die layout is shown.

In the lecture, we have discussed that in order to increase storage density, chipmakers might use an increased number of bits per cell (SLC -> MLC -> TLC -> QLC). However, this approach decreases performance and durability of the memory. Another appraoch was to simply shrink the size of the memory cells, to fit more cells on the same die area. This trend continued until the early 2010s, when physical and technical limitations made further shrinking impractical.

Since then, NAND manufacturers have taken another approach to increase storage density: stacking memory cells vertically, resulting in 3D NAND (also known as Vertical NAND or V-NAND) Flash Memory. Key advantages of 3D NAND over 2D NAND include increased speed, power efficiency, and a longer lifespan. A comparison of how 2D NAND and 3D NAND are structured is shown below:

![Image comparing 2D NAND and 3D NAND structures](res/1519405757965898353.jpg)

But how many layers are we actually talking about here? Are there any limits?

While early versions (for example by Micron, see sources) used 32 and later even 64 layers, modern 3D NAND chips can have over 200 layers. Examples include Kioxia’s 218-layer, Micron’s 232-layer, and Samsung’s 286-layer offerings. Recent headlines predict that in 2027, we might even see 500-layer 3D NAND chips with 4800 MT/s speeds. Not only do more layers increase the number of cells on the same die area, it also benefits internal latency by shortening paths and optimizing topology. However, the main limitation to the number of layers is the manufacturing process itself, as stacking more layers increases complexity and cost. The more steps are required to build the chip, the higher the chance of defects occurring during production. This might lead to lower yields and higher production costs. After all, manufacturers depend on commercial success, which is why they have to find a balance between yields (therefore also costs) and market demand.

Lastly, I would like to mention that in addition to stacking more layers vertically, manufacturers are also exploring PLC (penta-level cell) technology, which stores 5 bits per cell. This could further increase storage density, but also comes with its own set of challenges regarding performance and durability.

I found a lot of very interesting articles on this topic, but I was not able to include all the information in this report. So at least, I would like to share some sources for further reading:

My main sources which I can totally recommend are:
- [The Evolution of NAND Flash Memory](https://digitrendz.blog/newswire/technology/33981/the-evolution-of-nand-flash-memory/)
- [3D NAND Memory Forecast to 2027: Layers, Speed, and Storage Capacity](https://www.guiahardware.es/en/3D-NAND-memory-forecast-for-2027%3A-speed-and-storage-capacity/)

In addition, I've also used:
- [3D NAND Flash 再進化!!](https://www.hkepc.com/16749/3D_NAND_Flash_再進化_預計_2021_年可實現_140_層堆疊) - for graphics only!
- [The evolution of NAND - Micron Technology](https://www.micron.com/about/blog/memory/nand/the-evolution-of-nand)
- [Flashback : The Evolution of NAND Flash Technology - SK hynix](https://news.skhynix.com/flashback-the-evolution-of-nand-flash-technology/)
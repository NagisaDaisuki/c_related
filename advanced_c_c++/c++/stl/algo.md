<style>
    .color_036{
        color:#036aca;
        font-weight:bold;
    }    
</style>
<center><h2>分配器:allocator.h(一)</h2></center>
<h4><span style="color:blue;">1.什么是allocator(分配器)?</span></h4>

- allocator代表一种特定的<strong style="color:#036aca;">内存模型</strong>,将对内存的索求转变为对内存的<strong style="color:#036aca;">直接调用</strong>。
- allocator用于实现<strong style="color:#036aca">内存的分配和回收</strong>及<strong style="color:#036aca">对象的构造和销毁</strong>。该类向外部提供了四种可用接口来实现一个对象动态内存上的生命周期
<br />
 <code style="color:red;">分配内存(分配n个未初始化的T类内存) ---> (使用构造函数)初始化该内存上的对象 ---> (调用该对象的析构函数)销毁对象 ---> 释放内存</code>
 <br />
 
| Allocator |  |
| :---- | :---- | 
| <span style="color:#036aca;font-weight:bold;">内存的分配和回收</span> |<span style="color:#036aca;font-weight:bold;">对象的构造和销毁</span> |
| allocate(size_type n) | construct(T* ptr,T& value) |
| deallocate(T* ptr,size_type n) | destroy(T* ptr) |

由上可知，使用allocate()分配的内存的原始的、未构造的(即内存上为n个未初始化的空的T
类对象,里面的值是随机的、未知的)，所以申请完内存后，就要使用constrcut()在该内存上初始化该T类型的对象(因为使用未定义的内存，其行为是未定义的，不可预期的)。当我们使用完对象后，必须使用destroy()来调用该对象的析构函数来销毁它们，当内存上的对象被销毁后，就可以再次对其进行操作，即在上面构造其他本类对象/释放内存。    
~~~
allocator的接口使用: 

std::allocator<std::string> a;
auto const p = a.allocate(n);
a.construct(p,val/args);
a.destory(p);
a.deallocate(p,n);
~~~
<h4><span style="color:blue;">2.allocator()和new()的区别?</span></h4>

- allocator帮助我们<strong style="color:#036aca;">将内存分配和对象构造分离开来</strong>。它分配的内存是<strong style="color:#036aca;">原始的、未构造的</strong>。即allocate()出的内存是未初始化的（即划了块地。这块地原来上面是什么，现在还是什么），所以需要接着用construct()初始化它。这样分离成two-stage的设计使得用户可以在大块内存的使用时可以按需构造对象，从而避免不必要的浪费（避免多余的default ctor）。
  - <strong style="color:#036aca;">allocator的缺点：</strong>
  - <strong style="color:#036aca;">1.时刻记债：</strong>由上面的接口可知，如果使用allocate()来分配内存，那deallocate()释放内存时还需要将申请的内存大小作为参数传入，即从申请到释放的整个周期都需要知道自己要了多少内存，这就导致如果直接使用allocator来分配内存太容易出错了。所以allocator往往被当作template实参/构造函数实参传递给容器，然后保存在其内部，为容器分配内存。也正是由于分配器的存在，容器和算法得以参数化他们的元素存储方式
- new<strong style="color:#036aca;">将内存分配和对象构造</strong>组合在了一起，它分配的内存是默认初始化的，即分配内存后立即初始化(默认构造)一个该类的空对象(也可以在new T[N]的后面加上()调用该类对象的default ctor或者初值列{}来对这些有定义的内存上的空对象进行<strong style="color:#036aca">值初始化</strong>)。即new申请的内存空间上的对象一定执行过该类的default ctor 
  - <strong style="color:#036aca;">new的缺点：</strong>
  - <strong style="color:#036aca;">1.可能造成不必要的浪费：</strong>分配单个对象时，由于我们几乎肯定知道我们想要一个怎样的<span class="color_036">初值</span>对象，所以我们希望将内存的分配和对象初始化放在一起，此时new不会造成浪费。但当分配一大块内存时，我们往往不知道我们要给创建出的对象赋什么初始值，所以在使用时再按需在这块内存上<span class="color_036">构造不同value的T类对象</span>才是合理的，此时new分配出的内存就造成了很大的浪费，其一，当我们以T类型申请了一大块内存，但此时只需要x个T类型的对象时，救会导致在(n - x)*sizeof(T)的内存空间上创建了n-x个我们可能永远也用不到的T类型对象，这些<span class="color_036">多余的default ctor</span>造成了浪费。其二，在申请一大块内存时，我们往往不知道我们要给创建出的对象赋什么值，即我们在使用时，会对new出的对象进行再一次赋值，此时这个对象就会经历两次赋值，这也造成了浪费
  - <span class="color_036">2.没有默认构造函数的类不能用new为其动态分配内存</span>，这是非常重要的!
<h4><span style="color:blue;">3.选择合适的动态内存分配方法：</span></h4>

- 在需要大量未初始化的内存时，使用适合的容器(其内部使用的是allocator来分配内存)
- 在需要少量且已知要赋什么初始的内存时，使用new/delete（C++关键字）或malloc/free(这是C库函数)






 
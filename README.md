# PolysAndLines
For netvision


<h3 align="center">Привет! Ниже представлено описание этой програмки...</h3>

<p><big>Файлы.</big></p>
polys.cpp - основной файл программы, содержит внутри себя main ф-ию. 
object.cpp/.h - файлы класса object, который формирует "полигоны" фигуры и просчитывает пересечение линий с ним. 

<p><big>Краткое описание алгоритма..</big></p>
Нахождение статуса линии, относительно прямой, находится по пересечениям линий. Тонее так: фигура делится на линии и после этого находится все возможные линии пересечения <p><del>а точнее находятся уравнения прямых и... приравниваются...</del></p>.
Уравнения были выведены из классического: (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1). Далее находятся коэфициенты <p><strong>A</strong></p>, <p><strong>B</strong></p> и <p><strong>C</strong></p>. По ним уже можно проверить параллельность двух линий и так далее...
С параллельностью линий и в случаях их наложения пришлось прибегнуть к старинному способу проверки if(){}else{}, но зато работает, хоть и некрасиво... Также учитывается то, что при наложений двух линий, то засчитывается их пересечение. Если же полигон фигуры полностью перекрывает её, то линия считается ВНУТРИ фигуры.
Как указывалось выше: фигура может быть многоугольной. Впуклой или выпуклой. 
Нахождение линии относительно объекта находится при помощи посроения прямой между точкой фигуры и точкой линии, так происхожит со всеми точками (начальная точка линии + все точки фигуры, конечная точка линии + все точки фигуры). Если же кол-во пересечений будет равно кол-во точек фигуры * 2, то линия внутри. 
В противном случае - линия смотрим на кол-во пересечений. Чётное - линия полностью пересекает объект. Нечетное - линия пересекает одну из сторон объекта.

<p><big>На этом всё, спасибо за задание! </big></p>
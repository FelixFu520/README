##  **ONNX Python API**

⌚️: 2020年10月23日

📚参考

---



1. **Loading an ONNX Model**
2. **Saving an ONNX Model**
3. **ManipulatingTensorProtoand****NumpyArray**
4. **Creating an ONNX Model Using Helper****Functions**
5. **Checking an ONNX Model**
6. **Optimizing an ONNX Model**
7. **Running Shape Inference on an ONNX Model**
8. **UtilityFunctions**



**1 Loading an ONNX Model**

```python
import onnx

onnx_model = onnx.load('path/to/the/model.onnx')
# `onnx_model` is a ModelProto struct
```

**2 Saving an ONNX Model**

```python
import onnx

onnx_model = ... # Your model in memory as ModelProto

# Save the ONNX model
onnx.save(onnx_model, 'path/to/the/model.onnx')
```

**3 ManipulatingTensorProtoandNumpyArray**

```python
import numpy
import onnx
from onnx import numpy_helper

# Preprocessing: create a Numpy array
numpy_array = numpy.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]], dtype=float)
print('Original Numpy array:\n{}\n'.format(numpy_array))

# Convert the Numpy array to a TensorProto
tensor = numpy_helper.from_array(numpy_array)
print('TensorProto:\n{}'.format(tensor))

# Convert the TensorProto to a Numpy array
new_array = numpy_helper.to_array(tensor)
print('After round trip, Numpy array:\n{}\n'.format(numpy_array))

# Save the TensorProto
with open('tensor.pb', 'wb') as f:
    f.write(tensor.SerializeToString())

# Load a TensorProto
new_tensor = onnx.TensorProto()
with open('tensor.pb', 'rb') as f:
    new_tensor.ParseFromString(f.read())
print('After saving and loading, new TensorProto:\n{}'.format(new_tensor))
```

**4** **Creating an ONNX Model Using HelperFunctions**

```python
import onnx
from onnx import helper
from onnx import AttributeProto, TensorProto, GraphProto


# The protobuf definition can be found here:
# https://github.com/onnx/onnx/blob/master/onnx/onnx.proto


# Create one input (ValueInfoProto)
X = helper.make_tensor_value_info('X', TensorProto.FLOAT, [1, 2])

# Create one output (ValueInfoProto)
Y = helper.make_tensor_value_info('Y', TensorProto.FLOAT, [1, 4])

# Create a node (NodeProto)
node_def = helper.make_node(
    'Pad', # node name
    ['X'], # inputs
    ['Y'], # outputs
    mode='constant', # attributes
    value=1.5,
    pads=[0, 1, 0, 1],
)

# Create the graph (GraphProto)
graph_def = helper.make_graph(
    [node_def],
    'test-model',
    [X],
    [Y],
)

# Create the model (ModelProto)
model_def = helper.make_model(graph_def, producer_name='onnx-example')

print('The model is:\n{}'.format(model_def))
onnx.checker.check_model(model_def)
print('The model is checked!')
```

**5 Checking an ONNX Model**

```python
import onnx

# Preprocessing: load the ONNX model
model_path = 'path/to/the/model.onnx'
onnx_model = onnx.load(model_path)

print('The model is:\n{}'.format(onnx_model))

# Check the model
onnx.checker.check_model(onnx_model)
print('The model is checked!')
```

**6** **Optimizing an ONNX Model**

```python
import onnx
from onnx import optimizer

# Preprocessing: load the model to be optimized.
model_path = 'path/to/the/model.onnx'
original_model = onnx.load(model_path)

print('The model before optimization:\n{}'.format(original_model))

# A full list of supported optimization passes can be found here:
# https://github.com/onnx/onnx/blob/master/onnx/optimizer.py#L27
passes = ['fuse_consecutive_transposes']

# Apply the optimization on the original model
optimized_model = optimizer.optimize(original_model, passes)

print('The model after optimization:\n{}'.format(optimized_model))

# One can also apply the default passes on the (serialized) model
# Check the default passes here: https://github.com/onnx/onnx/blob/master/onnx/optimizer.py#L41
optimized_model = optimizer.optimize(original_model)
```

**7 Running Shape Inference on an ONNX Model**

```python
import onnx
from onnx import helper, shape_inference
from onnx import TensorProto


# Preprocessing: create a model with two nodes, Y's shape is unknown
node1 = helper.make_node('Transpose', ['X'], ['Y'], perm=[1, 0, 2])
node2 = helper.make_node('Transpose', ['Y'], ['Z'], perm=[1, 0, 2])

graph = helper.make_graph(
    [node1, node2],
    'two-transposes',
    [helper.make_tensor_value_info('X', TensorProto.FLOAT, (2, 3, 4))],
    [helper.make_tensor_value_info('Z', TensorProto.FLOAT, (2, 3, 4))],
)

original_model = helper.make_model(graph, producer_name='onnx-examples')

# Check the model and print Y's shape information
onnx.checker.check_model(original_model)
print('Before shape inference, the shape info of Y is:\n{}'.format(original_model.graph.value_info))

# Apply shape inference on the model
inferred_model = shape_inference.infer_shapes(original_model)

# Check the model and print Y's shape information
onnx.checker.check_model(inferred_model)
print('After shape inference, the shape info of Y is:\n{}'.format(inferred_model.graph.value_info))
```

**8 UtilityFunctions**

```python
import onnx
import onnx.utils


model = onnx.load('path/to/the/model.onnx')
polished_model = onnx.utils.polish_model(model)
```

注：各大框架对ONNX的支持还在完善中，所以有相当大部分功能是我们不能使用的，以下是我自己做实验的结果：


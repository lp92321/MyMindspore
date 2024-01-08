import mindspore
from mindspore import nn
from mindspore.dataset import vision, transforms
from mindspore.dataset import MnistDataset
import datetime
import matplotlib.pyplot as plt
import sys

# 指定map、batch、shuffle等操作。这里我们使用map对图像数据及标签进行变换处理，然后将处理好的数据集打包为大小为64的batch
def datapipe(dataset, batch_size):
    image_transforms = [
        # 基于给定的缩放和平移因子调整图像的像素大小。输出图像的像素大小 = image * 参数1 + 参数2
        vision.Rescale(1.0 / 255.0, 0),
        # 根据均值和标准差对输入图像进行归一化
        vision.Normalize(mean=(0.1307,), std=(0.3081,)),
        # 将输入图像的shape从 <H, W, C> 转换为 <C, H, W>。 如果输入图像的shape为 <H, W> ，图像将保持不变。
        vision.HWC2CHW()
    ]
    # 将输入的Tensor转换为指定的数据类型。
    label_transform = transforms.TypeCast(mindspore.int32)
    # 给定一组数据增强列表，按顺序将数据增强作用在数据集对象上。
    dataset = dataset.map(image_transforms, 'image')
    dataset = dataset.map(label_transform, 'label')
    # 将数据集中连续 batch_size 条数据组合为一个批数据
    dataset = dataset.batch(batch_size)
    return dataset

def visualize(dataset):
    figure = plt.figure(figsize=(4, 4))
    cols, rows = 3, 3

    plt.subplots_adjust(wspace=0.5, hspace=0.5)

    for idx, (image, label) in enumerate(dataset.create_tuple_iterator()):
        figure.add_subplot(rows, cols, idx + 1)
        plt.title(int(label))
        plt.axis("off")
        plt.imshow(image.asnumpy().squeeze(), cmap="gray")
        if idx == cols * rows - 1:
            break
    plt.show()

# mindspore.nn类是构建所有网络的基类，也是网络的基本单元。当用户需要自定义网络时，可以继承nn.Cell类，并重写__init__方法和construct方法。__init__包含所有网络层的定义，construct中包含数据（Tensor）的变换过程。
class Network(nn.Cell):
    def __init__(self):
        super().__init__()
        # 沿着从 start_dim 1到 end_dim 2的维度，对输入Tensor进行展平
        self.flatten = nn.Flatten()
        # 构造Cell顺序容器
        self.dense_relu_sequential = nn.SequentialCell(
            # 全连接层 参数12是输入和输出Tensor的空间维度（拉成一维）
            nn.Dense(28*28, 512),
            # 激活函数
            nn.ReLU(),
            nn.Dense(512, 512),
            nn.ReLU(),
            nn.Dense(512, 10)
        )

    def construct(self, x):
        x = self.flatten(x)
        logits = self.dense_relu_sequential(x)
        return logits

def train(model, dataset, grad_fn, optimizer):
    size = dataset.get_dataset_size()
    # 将网络模型设置为训练模式
    model.set_train()
    for batch, (data, label) in enumerate(dataset.create_tuple_iterator()):
        # 求导函数:实际值logits不求导，用_代替
        # 返回：梯度
        (loss, _), grads = grad_fn(data, label)
        # 优化器（随机梯度下降）：梯度
        optimizer(grads)

        if batch % 100 == 0:
#            print(f"打印loss={loss},data={data},lable={label},batch={batch}")
            loss, current = loss.asnumpy(), batch
            print(f"训练 loss: {loss:>7f}  [{current:>3d}/{size:>3d}]")

# 除训练外，我们定义测试函数，用来评估模型的性能			
def test(model, dataset, loss_fn):
    num_batches = dataset.get_dataset_size()
    model.set_train(False)
    total, test_loss, correct = 0, 0, 0
    for data, label in dataset.create_tuple_iterator():
        pred = model(data)
        total += len(data)
        test_loss += loss_fn(pred, label).asnumpy()
        correct += (pred.argmax(1) == label).asnumpy().sum()
    test_loss /= num_batches
    correct /= total
    print(f"测试: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")

# 加载模型参数，并将其加载至模型上。
def load_checkpoint_to_net(model):
    # 加载checkpoint文件到model中
    param_dict = mindspore.load_checkpoint("model.ckpt")
    #将参数加载到网络中，返回网络中没有被加载的参数列表param_not_load和checkpoint文件中没有被加载的参数列表ckpt_not_load
    param_not_load, _ = mindspore.load_param_into_net(model, param_dict)
    print('没有被加载的参数列表=',param_not_load)
    return model

# 加载后的模型可以直接用于预测推理。
def use_model(model, test_dataset):
    model.set_train(False)
    for data, label in test_dataset:
        pred = model(data)
        predicted = pred.argmax(1)
        print(f'开始推理Predicted: "{predicted[:10]}", Actual: "{label[:10]}"')
        break

def py_fun(train_data_path,test_data_path):
    print("111数据处理=", datetime.datetime.now())
    # MNIST数据集 生成的数据集有两列: [image, label]。
    train_dataset = MnistDataset(train_data_path)
    test_dataset = MnistDataset(test_data_path)
#    print(f'train_dataset数据列名={train_dataset.get_col_names()}')
#    print(f'test_dataset数据列名={test_dataset.get_col_names()}')

#    visualize(train_dataset)

    # Map vision transforms and batch dataset
    train_dataset = datapipe(train_dataset, 32)
    test_dataset = datapipe(test_dataset, 32)

    print("222数据处理=", datetime.datetime.now())
#    print(f'test_dataset分批后数据列名={test_dataset.get_col_names()}')
    model = Network()
    loss_fn = nn.CrossEntropyLoss()
    # 实例化对象，随机梯度下降的实现(学习率)
    optimizer = nn.SGD(model.trainable_params(), 1e-2)
    print("333数据处理=", datetime.datetime.now())
    # 前置函数
    def forward_fn(data, label):
        logits = model(data)
        # 损失函数
        loss = loss_fn(logits, label)
        return loss, logits
    grad_fn = mindspore.value_and_grad(forward_fn, None, optimizer.parameters, has_aux=True)
    print("444数据处理，开始训练=", datetime.datetime.now())
    epochs = 3
    for t in range(epochs):
        print(f"Epoch {t+1}\n-------------------------------")
        train(model, train_dataset, grad_fn, optimizer)
        test(model, test_dataset, loss_fn)

    print("555数据处理，训练完毕=", datetime.datetime.now())

    # 模型训练完成后，需要将其参数进行保存
    # Save checkpoint
    mindspore.save_checkpoint(model, "model.ckpt")
    print("Saved Model to model.ckpt")

    # 重新实例化模型对象，构造模型
    model = Network()
    model = load_checkpoint_to_net(model)
    use_model(model, test_dataset)
    print("666数据处理，模型成功=", datetime.datetime.now())
    return 1

if __name__ == '__main__':
    py_fun("D:/MyGitLocalRepository/code_second/mindspore_designer/MNIST_Data/train",
    "D:/MyGitLocalRepository/code_second/mindspore_designer/MNIST_Data/test")







	
'''
模型训练
在模型训练中，一个完整的训练过程（step）需要实现以下三步：

正向计算：模型预测结果（logits），并与正确标签（label）求预测损失（loss）。

反向传播：利用自动微分机制，自动求模型参数（parameters）对于loss的梯度（gradients）。

参数优化：将梯度更新到参数上。

MindSpore使用函数式自动微分机制，因此针对上述步骤需要实现：

定义正向计算函数。

使用value_and_grad通过函数变换获得梯度计算函数。

定义训练函数，使用set_train设置为训练模式，执行正向计算、反向传播和参数优化。
'''


import numpy as np
from nltk.corpus import reuters # 路透社语料库
import re

# 编辑距离：两个单词之间，由其中一个单词转换成另一个单词所需要的最少单字符编辑操作次数


# 词典库
vocab = set(line.rstrip() for line in open('data/vocab.txt'))

# 输入错误单词word，返回所有候选集合
def generate_candidates(word):
    # 26个单字符
    letters = 'abcdefghijklmnopqrstuvwxyz'
    # word = 'abc'时，splits = [('', 'abc'), ('a', 'bc'), ('ab', 'c'), ('abc', '')]
    splits = [(word[:i],word[i:]) for i in range(len(word)+1)]
    # 生成插入操作时，编辑距离为1的单词
    inserts = [L+c+R for L,R in splits for c in letters]
    # 生成删除操作时，编辑距离为1的单词
    deletes = [L+R[1:] for L,R in splits if R]
    # 生成替换操作时，编辑距离为1的单词
    replaces = [L+c+R[1:] for L,R in splits if R for c in letters]

    candidates = set(inserts + deletes + replaces)
    # 过滤掉不在词典库中的单词
    return [word for word in candidates if word in vocab]

def generate_edit_two(word=''):
    """
    给定一个字符串，生成编辑距离不大于2的字符串。
    """
#     # 第一步，先生成编辑距离为1的候选集合。
#     edit_one = generate_candidates(word)
#     # 第二部，遍历编辑距离为1的候选集合，对每个元素都再次使用函数
#     all_lis = []
#     for i in edit_one:
#         all_lis.extend(generate_candidates(i))

    # 上边的方法也可以直接写成一个列表生成式
    return set([j for i in generate_candidates(word) for j in generate_candidates(i)])




# 构建语言模型bigram（Binary Gram语言模型）
def language_model():
    # 读取语料库
    categories = reuters.categories()
    corpus = reuters.sents() # 数据集corpus，sents()指定分类中的句子
    term_count = {}
    bigram_count = {}
    for doc in corpus:
        doc = ['<s>'] + doc
        for i in range(0,len(doc)-1):
            term = doc[i]
            bigram = doc[i:i+2]
            if term in term_count:
                term_count[term] += 1
            else:
                term_count[term] = 1

            bigram = " ".join(bigram)
            if bigram in bigram_count:
                bigram_count[bigram] += 1
            else:
                bigram_count[bigram] = 1

    temp = [term_count,bigram_count]
    return temp

# 用户打错概率统计
def channel_probability():
    channel_prob = {}
    for line in open("data/spelling_error.txt"):
        items = line.split(":")
        correct = items[0].strip() # 去除第一个首尾的空格
        mistakes = [item.strip() for item in items[1].strip().split(",")]
        channel_prob[correct] = {} #字典中嵌套字典，比如{“rain”:{"riin":0.5,"rein":0.5}}
        for mistake in mistakes:
            channel_prob[correct][mistake] = 1.0 / len(mistakes)
    return channel_prob



# # 测试
# if __name__ == "__main__":
#     channel_pro = channel_probability()
#     temp = language_model()
#     temp_count,bigram_count = temp[0],temp[1]
#     vocab = set([line.strip() for line in open("data/vocab.txt")])
#     V = len(temp_count.keys())
#
#     test_data = "loking" # 测试单词
#     candidates = generate_candidates(test_data) #生成所有的候选集合
#     probs = []
#     for candi in candidates:
#         prob = 0
#         if candi in channel_pro and test_data in channel_pro:
#             prob += np.log(channel_pro[candi][test_data])
#         else:
#             prob += np.log(0.0001)

if __name__ == "__main__":
    channel_prob = channel_probability()
    temp = language_model()
    term_count, bigram_count = temp[0], temp[1]
    vocab = set([line.strip() for line in open('data/vocab.txt')])

    V = len(term_count)
    # 打开测试数据
    with open("data/testdata.txt", 'r', encoding='utf8') as f:
        # 遍历每一行
        for line in f:
            # 去掉每一行右边的空格。并且以制表符来分割整个句子
            items = line.rstrip().split('\t')
            # items:
            # ['1', '1', 'They told Reuter correspondents in Asian capitals a U.S.
            # Move against Japan might boost protectionst sentiment in the  U.S. And lead to curbs on
            # American imports of their products.']
            # 把\.去掉，每个句子刚好在items的下标为2的位置。
            line = re.sub('\.', '', items[2])
            # 去掉逗号，并且分割句子为每一个单词，返回列表
            line = re.sub(',', '', line).split()
            # line:['They', 'told', 'Reuter', 'correspondents', 'in', 'Asian',
            # 'capitals', 'a', 'US', 'Move', 'against', 'Japan', 'might', 'boost', 'protectionst',
            # 'sentiment', 'in', 'the', 'US', 'And', 'lead', 'to', 'curbs', 'on', 'American', 'imports', 'of', 'their', 'products']
            # 遍历词语列表
            for word in line:
                # 去除每一个单词前后的逗号和句号。
                word = word.strip('.')
                word = word.strip(',')
                # 如果这个单词不在词库中。
                # 就要把这个单词替换成正确的单词
                if word not in vocab:
                    # Step1: 生成所有的(valid)候选集合
                    candidates_one = generate_candidates(word)
                    # 把生成的所有在词库中的单词拿出来。
                    candidates = [word for word in candidates_one if word in vocab]
                    # 一种方式： if candidate = [], 多生成几个candidates, 比如生成编辑距离不大于2的
                    # TODO ： 根据条件生成更多的候选集合
                    # 如果candidates为空的话，则接着生成编辑距离为2的。
                    if len(candidates) < 1:
                        candidates_two = generate_edit_two(word)
                        candidates = [word for word in candidates_two if word in vocab]
                        if len(candidates) < 1:
                            continue
                    probs = []

                    # 计算所有候选单词的分数。
                    # score = p(correct)*p(mistake|correct)
                    #       = log p(correct) + log p(mistake|correct)

                    #                 log p(mistake|correct)= log(p(correct/mistake)*p(mistake)/p(correct))

                    # 遍历候选词汇
                    # 返回score最大的candidate
                    # score既考虑了单个单词的概率，也考虑了与前边单词组合的概率。
                    for candi in candidates:
                        prob = 0

                        # a. 计算channel probability
                        # 如果候选词在channel_prob字典中，并且错误单词刚好在候选词对应的值处。
                        if candi in channel_prob and word in channel_prob[candi]:
                            prob += np.log(channel_prob[candi][word])

                        else:
                            prob += np.log(0.00001)

                        # b. 计算语言模型的概率
                        sentence = re.sub('\.', '', items[2])
                        # 得到单词在原来句子中的索引
                        idx = re.sub(',', '', sentence).split().index(word)
                        #
                        # items:
                        # ['1', '1', 'They told Reuter correspondents in Asian capitals a U.S.
                        # Move against Japan might boost protectionst sentiment in the  U.S. And lead to curbs on
                        # American imports of their products.']

                        # 把当前单词和他的前一个单词拼接到一起。
                        bigram_1 = ' '.join([items[2].split()[idx - 1], candi])

                        # 如果bigram_1在双字符词典里，并且前一个单词也在词典里
                        if bigram_1 in bigram_count and items[2].split()[idx - 1] in term_count:
                            prob += np.log((bigram_count[bigram_1] + 1.0) / (
                                    term_count[items[2].split()[idx - 1]] + V))
                        else:
                            prob += np.log(1.0 / V)
                        # TODO: 也要考虑当前 [word, post_word]
                        #   prob += np.log(bigram概率)

                        if idx + 1 < len(items[2].split()):
                            bigram_2 = ' '.join([candi, items[2].split()[idx + 1]])
                            if bigram_2 in bigram_count and candi in term_count:
                                prob += np.log((bigram_count[bigram_2] + 1.0) / (
                                        term_count[candi] + V))
                            else:
                                prob += np.log(1.0 / V)

                            # 所有候选单词的分数都添加到probs列表里。
                            probs.append(prob)
                    #
                    # print(probs)
                    if probs:
                        # 得到probs列表候选单词里最大的分数，把索引拿出来
                        max_idx = probs.index(max(probs))
                        # 该索引同时也对应着候选集合里的正确单词，输出错误单词和正确单词。
                        print(word, candidates[max_idx])
                    else:
                        print("False")



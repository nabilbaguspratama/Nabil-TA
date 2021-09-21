def transform(values):
    arr = []

    for item in values:
        arr.append(singleTransform(item))

    return arr


def singleTransform(values):
    return {
        "id": values.id,
        "min": values.min,
        "max": values.max,
        "mean": values.mean,
        "std_dev": values.stdev,
        "median": values.median,
        "variance": values.variance,
        "label": values.label
    }
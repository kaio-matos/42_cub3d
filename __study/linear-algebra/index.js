
/**
 *  @typedef Point
 *  @property {number} x
 *  @property {number} y
 */

function createPoint(x, y) {
    return { x, y }
}
function random(number) {
    return Math.random() * number
}

class Vector {
    #original_x = 0
    #original_y = 0
    #scalar = 1


    constructor(x, y) {
        this.#original_x = x
        this.#original_y = y
    }

    setScalar(multiplier) {
        this.#scalar = multiplier
        return this
    }

    getScalar() {
        return this.#scalar
    }

    copy() {
        return new Vector(this.#original_x, this.#original_y).setScalar(this.#scalar)
    }

    get x() {
        return this.#original_x * this.#scalar
    }

    get y() {
        return this.#original_y * this.#scalar
    }
}

class Canvas {
    interval
    context
    background

    #previousColors = {
        fillStyle: null,
        fillRect: null,
        strokeStyle: null
    }

    constructor(background) {
        const canvas = document.getElementsByTagName('canvas')[0]
        this.context = canvas.getContext('2d')
        this.background = background
        this.clear()
    }

    draw(callback) {
        this.interval = setInterval(() => {
            this.clear()
            callback(this.context.canvas)
        }, 100)
    }

    stop() {
        clearInterval(this.interval)
    }

    /**
     *
     * @param {Point} from
     * @param {Point} to
     */
    line(from, to) {
        this.context.beginPath();
        this.context.moveTo(from.x, from.y);
        this.context.lineTo(to.x, to.y);
        this.context.closePath()
        this.context.stroke();
    }

    /**
     * Draws a Vector
     * @param {Vector} vector
     */
    vector(vector) {
        const offsetWidth = this.context.canvas.width / 2
        const offsetHeight = this.context.canvas.height / 2
        const convertedCenter = createPoint(offsetWidth, offsetHeight)
        const normalizedVector = createPoint(vector.x, vector.y)

        const convertedVectorPosition = createPoint(
            Math.abs(normalizedVector.x + offsetWidth),
            Math.abs(normalizedVector.y - offsetHeight),
        )

        console.log(convertedVectorPosition)

        this.line(
            createPoint(convertedCenter.x, convertedCenter.y),
            createPoint(convertedVectorPosition.x, convertedVectorPosition.y)
        )
    }

    clear() {
        this.color(this.background)
        this.context.rect(0, 0, this.context.canvas.width, this.context.canvas.height)
        this.context.fill()
        this.resetColor()
    }

    color(color) {
        this.#previousColors.strokeStyle = this.context.strokeStyle
        this.#previousColors.fillRect = this.context.fillRect
        this.#previousColors.fillStyle = this.context.fillStyle
        this.context.fillStyle = color
        this.context.fillRect = color
        this.context.strokeStyle = color
    }

    resetColor() {
        this.context.fillStyle = this.#previousColors.fillStyle
        this.context.fillRect = this.#previousColors.fillRect
        this.context.strokeStyle = this.#previousColors.strokeStyle
    }
}

const canvas = new Canvas('#fff')

const vector = new Vector(10, 1)

vector.setScalar(1)

// canvas.draw(() => {
//     canvas.color('blue')
//     for (let i = 0; i < 1000; i++) {
//         canvas.line(createPoint(250, 500), createPoint(random(500), random(250)))
//     }
// })

canvas.draw(() => {
    vector.setScalar(vector.getScalar() + 10)
    canvas.color('blue')
    canvas.vector(vector)
})



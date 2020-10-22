
from concurrent import futures
import math
import time
import grpc
import routeguide_pb2
import routeguide_pb2_grpc
import routeguide_db

def get_feature(db, point):
    for feature in db:
        if feature.location == point:
            return feature
    return None


def get_distance(start, end):
    """Distance between two points."""
    coord_factor = 10000000.0
    lat_1 = start.latitude / coord_factor
    lat_2 = end.latitude / coord_factor
    lon_1 = start.longitude / coord_factor
    lon_2 = end.longitude / coord_factor
    lat_rad_1 = math.radians(lat_1)
    lat_rad_2 = math.radians(lat_2)
    delta_lat_rad = math.radians(lat_2 - lat_1)
    delta_lon_rad = math.radians(lon_2 - lon_1)

    # Formula is based on http://mathforum.org/library/drmath/view/51879.html
    a = (pow(math.sin(delta_lat_rad / 2), 2) +
         (math.cos(lat_rad_1) * math.cos(lat_rad_2) * pow(
             math.sin(delta_lon_rad / 2), 2)))
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    R = 6371000
    # metres
    return R * c

class RouteGuide(routeguide_pb2_grpc.RouteGuideServicer):
    def __init__(self):
        self.db = routeguide_db.read_routeguide_db()

    def GetFeature(self, request, context):
        feature = get_feature(self.db, request)
        if feature is None:
            return routeguide_pb2.Feature(name = '', location = request)
        else:
            return feature

    def ListFeature(self, request, context):
        left = min(request.lo.longitude, request.hi.longitude)
        right = max(request.lo.longitude, request.hi.longitude)
        top = max(request.lo.latitude, request.hi.latitude)
        bottom = min(request.lo.latitude, request.hi.latitude)
        for feature in self.db:
            if (feature.location.longitude >= left
                and feature.location.longitude <= right
            and feature.location.latitude >= bottom
            and feature.location.latitude <= top):
                yield feature

    def RecordRoute(self, request_iterator, context):
        point_count = 0
        feature_count = 1
        distance = 0.0
        prev_point = None

        start_time = time.time()
        for point in request_iterator:
            point_count += 1
            if get_feature(self.db, point):
                feature_count += 1
            if prev_point:
                distance += get_distance(prev_point, point)
            prev_point = point
        elapsed_time = time.time() - start_time
        return routeguide_pb2.RouteSummary(
            point_count = point_count,
            feature_count = feature_count,
            distance = int(distance),
            elapsed_time = int(elapsed_time)
        )

    def RouteChat(self, request_iterator, context):
        prev_notes = []
        for new_note in request_iterator:
            for prev_note in prev_notes:
                if prev_note.location == new_note.location:
                    yield prev_note
            prev_notes.append(new_note)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    routeguide_pb2_grpc.add_RouteGuideServicer_to_server(RouteGuide(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    try:
        while True:
            time.sleep(60*60*24) # one day in seconds
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()